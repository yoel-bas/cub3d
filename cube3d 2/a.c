#include <stdio.h>
#include "../MLX42/include/MLX42/MLX42.h"

int	main() {
	mlx_t *mlx = mlx_init(1024, 600, "cube", 0);
	//mlx_image_t *image = mlx_new_image(mlx, 1024, 600);
	mlx_loop(mlx);
}

