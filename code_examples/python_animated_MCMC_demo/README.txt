You can run the example script as: 

  python3 MCMC_demo.py

Towards the beginning of the script there are six code blocks with settings 
for six different example runs. Read the discriptions below and uncomment the 
settings for the example you want to run.


General explanation of plots
----------------------------

Top panel:
- The black graph shows the true pdf p(x) that we want to use MCMC to sample from
- The black dotted lines marks the true mean <x> for the pdf p(x)
- The red dot marks the current position / state x in the MCMC chain
- The yellow histogram shows the histogram of x samples gathered so far in the MCMC run
- The red dotted line shows the sample mean value computed from the x samples

Bottom panel:
- Shows the corresponding samples collected for some arbitrary derived quantity f 
  that is computed for each x sample. 
- The dotted blue line shows the sample average of the f samples
- (The true distribution for f is unknown.)


Example 1
---------
- A standard MCMC run (with only 100 samples) starting
  from a high-probability initial state.

Example 2
---------
- Same as example 1, but now starting from a very low-probability
  starting point. 
- Here we see the burn-in problem: Since we cannot gather an infinite
  number of samples our sample distribution (and corresponding sample mean, variance, ...)
  can be strongly dependent on the starting point of the MCMC run. 

Example 3
---------
- Same as example 2, but with many more samples.
- Notice how the burn-in problem is now less severe. 

Example 4
---------
- Example with multimodal (multiple peaks) true pdf
- Can get challenging for a single MCMC chain ("walker")
  to discover/explore all modes in a pdf, especially in many
  dimensions.
- You can try shifting the peaks further apart or making them more narrow.

Example 5
---------
- Similar to example 4, but with many more samples
- Notice how we now also get a smooth-looking distribution
  for the derived quantity f

Example 6
---------
- Change the line "accept_ratio = p(x_proposal) / p(x_current)" towards the end
  of the script to "accept_ratio = 1.0"
- Run the example
- This demonstrates how the acceptance rule (which was chosen to ensure the requirement 
  of "detailed balance") is necessary for the chain to actually draw samples from the
  desired pdf p(x)

