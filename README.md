# Lorenz

## Compile

```bash
gcc -o lorenz lorenz.c
```

## Lorenz attractor 


$$\phi_X^{n+1} = \phi_X^n + \Delta t~(-\sigma X~+~\sigma Y)$$

$$\phi_Y^{n+1} = \phi_Y^n + \Delta t~(-XZ~+~rZ~-~Y)$$

$$\phi_Z^{n+1} = \phi_Z^n + \Delta t~(XY~-~bZ)$$

$$\frac{d\vec{x}}{dt}=f_D(\vec{x}) ~ + ~ f_K(\vec{x})$$


### Example

![Example](example/lorenz_rk.png)

![Example](example/lorenz_euler.png)


