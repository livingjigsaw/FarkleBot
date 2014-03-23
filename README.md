FarkleBot
=========

please commit and push to main dev branch, and only merge to master after testing code and proving that it works

ACU Research festival entry that learns how to play the dice game Farkle using a simple genetic algorithm.

genetic algorithm parameters are weights applied to different factors that affect the decision to roll again. the factors are

opponent's score / 10000
maximum opponent's score - my score / 10000; the bigger, the riskier we'll be as we are farther behind
number of dice left to roll/6
current turn's score / 1000; 1000 was arbitrarily chosen, definitely up for discussion
