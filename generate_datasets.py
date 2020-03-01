import os

import sklearn.datasets as datasets
import pandas as pd


def generate_dataset(points, n_features, centers, std, file_name, output_directory):
    data, __ = datasets.make_blobs(
        points, n_features, centers, cluster_std=std, shuffle=True,
        random_state=1000
    )
    pd.DataFrame(data).to_csv(
        os.path.join(output_directory, file_name), header=False, index=False
    )


def main():

    dataset_num = 1

    '''Datasets with std=1 and well defined clusters'''

    DATASETS_DIR = 'datasets/different_clusters/'

    # two dimensional datasets
    for c in range(1, 6):
        generate_dataset(points=10000, n_features=2, centers=c, std=1, file_name=f'2D_data_{c}.csv', output_directory=DATASETS_DIR)
        dataset_num += 1

    # three dimensional datasets

    dataset_num = 1
    for c in range(1, 6):
        generate_dataset(points=10000, n_features=3, centers=c, std=1, file_name=f'3D_data_{c}.csv', output_directory=DATASETS_DIR)
        dataset_num += 1

    '''Datasets with an increasing number of points'''

    DATASETS_DIR = 'datasets/different_size/'

    dataset_num = 1

    # two dimensional datasets
    for points in [100, 1000, 10000, 20000, 50000]:
        generate_dataset(points, n_features=2, centers=5, std=1, file_name=f'2D_data_{points}.csv', output_directory=DATASETS_DIR)
        dataset_num += 1

    # three dimensional datasets

    dataset_num = 1
    for points in [100, 1000, 10000, 20000, 50000]:
        generate_dataset(points, n_features=3, centers=5, std=1, file_name=f'3D_data_{points}.csv', output_directory=DATASETS_DIR)
        dataset_num += 1


if __name__ == '__main__':
    main()