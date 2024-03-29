# FinalProject18

Woodrow Wilson High School, Portland, OR

James Wheeler III

This is a repository of all of the components for what is my final project for my AP Physics, and Computer Science classes of my senior year. A portion of this is also considered one of the many projects I completed for my Shop class. The project, in theory, is simple. To create a Newton's Cradle that can tell you when the outwards marbles pass the sides of the cradle. This apparatus can then perform a series of experiments based around comparing some factor within the cradle by the factor of time. Below is the project proposals given to both my AP Physics teacher, and my Computer Science Teacher.

# AP Physics:
    The proposed experiment is to create an apparatus, henceforth referred to as ‘The Cradle’ that will be able to measure, to a fairly accurate degree, the timing within a Newton’s Cradle. The data from The Cradle will then be graphed, linearized as needed, and calculated to determine the relationships within a Newton’s Cradle. 

    The Cradle itself will be made from sheet aluminum, high quality fishing line, a series of ball bearings, and a number of internal circuits. The circuits will be custom designed by the experiment conductors, and will include a series of IR receivers, and IR emitters. These will be in two pairs known as ‘IR Gates’ that will determine when an object gets between the pair, sending the moment of interruption over serial to a computer to log the number of interruptions over unit time.

    There are a number of uncertainties generated by The Cradle within the date. The most likely of them being an IR signal bouncing around an interrupting object, and creating a false negative in the system. This has been noted, and the current solution is to send a specific byte of data over IR between the gates, and determine either no data, or data that doesn’t match the original byte to be a point of interrupt.

# Computer Science:
    I am writing a program that will take in input from one of the USB ports, with the information referring to a true/false from one of two inputs. A display will be shown for the user, showing when one side or the other is true or false. This will be represented by two dots on screen, red while false, with green while true. In the background, a spreadsheet will be created, saying when each of the inputs have been confirmed true, as well as the time at which true was sent.
