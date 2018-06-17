**Problem description**: Estimate $\pi$ to three decimal places using a Monte Carlo method.

One possible way to solve this problem is to exploit the fact that the area of a circle having radius $R$ can be computed as

$$A = \pi R^{2}$$

If we were given an estimate of the circle area $A^{*}$, we could compute an estimate of $\pi$ via a simple division 

$$\pi \approx \frac{A^{*}}{R^{2}}$$

**Question**: how can we obtain an estimate of the area of a circle having radius $R$ (without using the well-known formula that is)?  
**Answer**: by using Monte Carlo sampling

---

Let's elaborate this further:  
Suppose we are given a square area and that the area side length is $2R$.  
Suppose, moreover, that we want to sample points from this area and that all the points in the area are equiprobable.

We know that the probability density function in this case is  
$$pdf(x) = \frac{1}{A_{square}} = \frac{1}{4R^{2}}$$

Let's now inscribe a circumference having radius $R$ inside our square area, how can we compute the probability of picking a point from the square area, which is also contained inside the crf?  
We can do this by integrating the probability density function we described above on the domain defined by the inscribed circumference.  
Since the density function is constant all over the square area, the computations are trivial and
$$P(crf) = \frac{A_{crf}}{A_{square}} = \frac{\pi R^{2}}{4R^{2}} = \frac{\pi}{4}$$

From this equation we can easily derive
$$\pi = 4 \, P(crf)$$

But how can we compute the probability of picking a point inside the crf without computing its area?  
Well, we can use sampling:
1. Define a 2D reference frame and consider both the square area and the cricumference centered on its origin
2. Reset counters `#crf_counter` and `#sample_counter`, which are used respectively to count the number of samples drawn from within the crf and the total number of drawn samples
3. Sample a point $(x, y)$ from the uniform 2D distribution we defined on the square area
4. Check if the point is contained inside the crf (i.e. $x^{2} + y^{2} \lt R$) and, in the affirmative case, increment `#crf_counter`
5. Increment `#sample_counter`
6. Repeat from 3. until enough samples have been drawn.

We can then estimate $P(crf)$ using the following equation:
$$P(crf) = \frac{\#crf\_counter}{\#sample\_counter}$$

To recap:

$$\pi \approx 4 \frac{\#crf\_counter}{\#sample\_counter}$$

---

**Are we done yet?**  
**One last thing**: how many samples are required in order to estimate $\pi$ to three decimal places?

We use a rule-of-thumb for this -> it has been shown that the uncertainty on the estimation using MCL is proportional to 
$$\sigma = \frac{1}{2\sqrt{N}}$$
where $N$ is the number of samples.

In our case $\sigma = 1e^{-3}$ so we need at least one million of samples