import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


EXECUTABLE = '../MeanShift/cmake-build-releasepar/meanshift'


def main():
    output_file = "/output"

    data = np.genfromtxt('{}.csv'.format(output_file), delimiter=',')
    num_clusters = int(np.max(data[:, -1] + 1))
    clusters = np.ndarray(shape=num_clusters, dtype=np.ndarray)
    for i in range(0, num_clusters):
        clusters[i] = np.float32(
            [point[:-1] for point in data if point[-1] == i]
        )
    fig = plt.figure()
    if len(clusters[0][0]) == 2:
        # 2D plot
        for cluster in clusters:
            plt.scatter(cluster[:, 0], cluster[:, 1], s=3)
    else:
        # 3D plot
        ax = Axes3D(fig)
        for cluster in clusters:
            ax.scatter(cluster[:, 0], cluster[:, 1], cluster[:, 2], s=3)
    plt.show()
    # os.remove('{}.csv'.format(output_file))


if __name__ == '__main__':
    main()
