Meaning of the points

P: position of the player (posX, posY)

H: hitpoint of thr ray on the wall. Its y position is known to be mapY + (1 - stepY) / 2

yDist : matches "(mapY + (1 - stepY) / 2 - posY)", this is the y coordinate of the Euclidean distance vector, in world coordinates. Here, (1 - stepY) / 2) is a correction term that is 0 or 1 based on positive or negative y direction, which is also used in the initialization of sideDistY.

dir: the main player looking direction, given by dirX,dirY in the code. The length of this vector is always exactly 1. This matches the looking direction in the center of the screen, as opposed to the direction of the current ray. It is perpendicular to the camera plane, and perpWallDist is parallel to this.

orange dotted line (may be hard to see, use CTRL+scrollwheel or CTRL+plus to zoom in a desktop browser to see it better): the value that was added to dir to get rayDir. Importantly, this is parallel to the camera plane, perpendicular to dir.

A: point of the camera plane closest to H, the point where perpWallDist intersects with camera plane
B: point of X-axis through player closest to H, point where yDist crosses the world X-axis through the player
C: point at player position + rayDirX
D: point at player position + rayDir.
E: This is point D with the dir vector subtracted, in other words, E + dir = D.

points A, B, C, D, E, H and P are used in the explanation below: they form triangles which are considered: BHP, CDP, AHP and DEP