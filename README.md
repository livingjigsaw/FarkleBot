FarkleBot
=========

This was a project for an undergraduate Pattern Recognition class, where we were given freedom to select a learning algorithm and a problem to apply it to. 

So, this project was to create a genetic algorithm that could play the dice game Farkle, and allow people to play against the bots.

Currently, the system has a design that is rather extensible, but the implementation is still rudimentary, and has not been through much testing at all. It's written exclusively in C++, and can currently compile by including all the cpp files without additional libraries. 

There are 40 bots per generation, the bot's score is determined by letting it play 20 turns, and the next generation is created by averaging the score from the top 5% of bots created, and forcing a "normal" distribution. The number being reported is the top bot's score, not the average.

Initial analysis of results shows that the current genetic algorithm doesn't seem to be changing notably over time. Using more bots per generation seems to increase the lower bound and more extended generations may reveal more variation, but only having three parameters being weighed may not be creating diverse enough bevavior in the bots, and the parameters themselves may not be affecting them much. 

In short, it's not much right now, needs refining for more definitive results, and playing against other people and bots is mostly untested.