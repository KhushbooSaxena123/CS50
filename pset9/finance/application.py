
import os
import pytz

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask.helpers import get_flashed_messages
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # initializing the total cash.
    total = 0.0
    Id = session["user_id"]
    row = db.execute("SELECT * FROM users WHERE id = ?", Id)
    username = row[0]['username']
    rows = db.execute("SELECT * FROM purchase WHERE username = ?", username)
    cash = row[0]['cash']

    # Calculating the total cash.
    for r in rows:
        total = total + r['price']*r['shares']
    total = total + cash

    # simply get the index page.
    return render_template("index.html", rows=rows, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # if the mathod is post chacking if all the requirement is fullfilled.
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        if symbol and (lookup(symbol) is None):
            return apology("must provide a valid symbol", 400)

        # checking if shares should not be a negative or fraction or an non-numeric number.
        shares = request.form.get("shares")
        if not shares:
            return apology("must provide shares", 400)

        if shares.isalpha():
            return apology("must provide valid shares", 400)

        try:
            shares = int(shares)
            if shares < 1:
                return apology("share must be a positive integer", 400)
        except ValueError:
            return apology("share must be a positive integer", 400)

        Id = session["user_id"]
        row = db.execute("SELECT * FROM users WHERE id = ?", Id)
        cash = row[0]['cash']
        username = row[0]['username']
        Local = pytz.timezone('Asia/Kolkata')
        X = datetime.now(tz=Local).strftime("%Y-%m-%d %H:%M:%S")

        # checking if user have that much cash available to buy a particular share.
        if cash >= ((lookup(symbol)['price'])*(shares)):
            db.execute("INSERT INTO purchase(username, symbol, company_name, price, shares, datetime) VALUES(?, ?, ?, ?, ?, ?)",
                       username, symbol, lookup(symbol)['name'], lookup(symbol)['price'], shares, X)
            db.execute("INSERT INTO records(username, symbol, company_name, price, shares, datetime) VALUES(?, ?, ?, ?, ?, ?)",
                       username, symbol, lookup(symbol)['name'], lookup(symbol)['price'], shares, X)
            updated_cash = cash - ((lookup(symbol)['price'])*shares)
            db.execute("UPDATE users SET cash = ? WHERE username = ?", updated_cash, username)
            flash("Bought")
            return redirect("/")

        else:
            return apology("You do not have sufficient cash to purchase these shares at current price")

    # simply get the buy page.
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Selecting the loged in user.
    Id = session["user_id"]
    row = db.execute("SELECT * FROM users WHERE id = ?", Id)
    username = row[0]['username']

    # Selecting the row from the records
    rows = db.execute("SELECT * FROM records WHERE username = ? ORDER BY datetime DESC", username)

    # Displaying the records of the user by history page.
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a stock's symbol", 400)
        elif lookup(symbol) is None:
            return apology("Incorrect stock's symbol", 400)
        else:
            row = lookup(symbol)
            return render_template("quoted.html", row=row)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # If the mathod is post chacking all the rquirement is fullfil.
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        elif username:
            users = db.execute("SELECT username FROM users")
            for user in users:
                if username in user["username"]:
                    return apology("username is not available", 400)

        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # Checking if the the password and confirmation password matches.
        if password != request.form.get("confirmation"):
            return apology("password and confirmation password should match", 400)

        # Adding the new user into the users table
        db.execute("INSERT INTO users(username, hash) VALUES(?,?)", username, generate_password_hash(password))

        # Simply redirecting to the login page.
        return redirect("/login")

    else:

        # Otherwise simply get the registration page.
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    Id = session["user_id"]
    row = db.execute("SELECT * FROM users WHERE id = ?", Id)
    username = row[0]['username']
    cash = row[0]['cash']
    rows = db.execute("SELECT * FROM purchase WHERE username = ?", username)

    # If the method is post insure all the requirment is fullfil.
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must select a symbol", 400)

        shares = int(request.form.get("shares"))
        if not shares:
            return apology("musch provid shares", 400)

        if shares < 0:
            return apology("musch provid a valid number of shares", 400)

        if shares > 0:
            for r in rows:
                if r['symbol'].lower() == symbol.lower():

                    # checking if that much number of shares exis or not.
                    if int(r['shares']) < shares:
                        return apology("You do not have this much shares", 400)
                    else:

                        # Updating the cash in the user and purchase table after selling the shares.
                        updated_cash = cash + ((lookup(symbol)['price'])*shares)
                        db.execute("UPDATE users SET cash = ? WHERE username = ?", updated_cash, username)
                        updated_shares = int(r['shares']) - shares
                        db.execute("UPDATE purchase SET shares = ? WHERE username = ? and symbol = ?",
                                   updated_shares, username, symbol)

                        # Updating the Sell and record table after selling the shares.
                        Local = pytz.timezone('Asia/Kolkata')
                        X = datetime.now(tz=Local).strftime("%Y-%m-%d %H:%M:%S")
                        db.execute("INSERT INTO sell(username, symbol, company_name, price, shares, datetime) VALUES(?, ?, ?, ?, ?, ?)",
                                   username, symbol, lookup(symbol)['name'], lookup(symbol)['price'], -shares, X)
                        db.execute("INSERT INTO records(username, symbol, company_name, price, shares, datetime) VALUES(?, ?, ?, ?, ?, ?)",
                                   username, symbol, lookup(symbol)['name'], lookup(symbol)['price'], -shares, X)

                        # redirecting at the index page
                        flash("Sold")
                        return redirect("/")

    # Otherwise simply get the sell page.
    return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
