import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

logged_username = ""
logged_id = 0


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing or incorrect ticker symbol")
        elif not request.form.get("shares"):
            return apology("Please input numbers of shares to buy")

        symbol_lookup = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        total_amount = float(symbol_lookup["price"]) * int(shares)
        cash_left = db.execute(
            ("SELECT cash FROM users WHERE id = ?", logged_id))

        return render_template("inquiry.html", symbol_lookup=symbol_lookup, shares=shares, total_amount=total_amount, cash_left=cash_left)

    #     if (symbol_lookup.price == "None" or symbol_lookup.symbol == "None"):
    #         return apology("Didn't find the ticker symbol")
    #
    #     # user_username = db.execute(
    #     #     "SELECT username FROM users WHERE id = ?", session["user_id"])
    #     # user_cash = db.execute(
    #     #     "SELECT cash FROM users WHERE id = ?", session["user_id"])
    #     # cash_left = user_cash - (shares * symbol_lookup.price)

    #     # db.execute("CREATE TABLE purchases (user_id INT AUTOINCREMENT NOT NULL, username TEXT NOT NULL, shares NUMERIC NOT NULL, symbol TEXT NOT NULL, price_puchased NUMERIC NOT NULL, cash_left NUMERIC NOT NULL)")

    #     # db.execute(
    #     #     "INSERT INTO purchases (username, shares, symbol, price_purchased, cash_left) VALUES (?, ?, ?, ?, ?)", user_username, shares, symbol_lookup.symbol, symbol_lookup.price, cash_left)
    #     return render_template("purchased.html", symbol_lookup=symbol_lookup)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()
    global logged_username
    global logged_id

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        logged_id = rows[0]["id"]
        logged_username = rows

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

        if not request.form.get("symbol"):
            return apology("Please input a ticker symbol.", 405)
        symbol_lookup = lookup(request.form.get("symbol"))

        return render_template("quoted.html", symbol_lookup=symbol_lookup)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Username missing", 403)
        elif not request.form.get("password"):
            return apology("Missing password", 403)
        elif not request.form.get("confirmation") or (request.form.get("password") != request.form.get("confirmation")):
            return apology("Passwords not matching", 403)

        username = request.form.get("username")
        password = request.form.get("password")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   username, generate_password_hash(password))
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
