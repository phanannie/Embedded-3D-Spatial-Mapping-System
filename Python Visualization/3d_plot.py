import numpy as np
import open3d as o3d

if __name__ == "__main__":
    # Read the point cloud data
    pcd = o3d.io.read_point_cloud("distance_data.xyz", format='xyz')
    
    # Calculate the total number of points
    numpoints = len(pcd.points)

    lines = []

    # Calculating num of slices using 32 scans per rot
    num_slices = numpoints // 32

    for slice_index in range(num_slices):
        # Connect the points within each slice
        base_index = 32 * slice_index
        for point_index in range(31):  # 32 points, but connect each to the next, so only 31 connections
            lines.append([base_index + point_index, base_index + point_index + 1])
        # Connect the last point in the slice back to the first to complete the circle
        lines.append([base_index + 31, base_index])

    # Connect corresponding points between adjacent slices
    for slice_index in range(1, num_slices):
        for point_index in range(32):
            lines.append([32 * (slice_index - 1) + point_index, 32 * slice_index + point_index])

    # Create a line set from the points and the connections we defined
    line_set = o3d.geometry.LineSet(
        points=o3d.utility.Vector3dVector(np.asarray(pcd.points)),
        lines=o3d.utility.Vector2iVector(lines)
    )

    # Draw the line set
    o3d.visualization.draw_geometries([line_set])
