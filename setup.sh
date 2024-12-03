#!/bin/bash
# Download the IMDb datasets
curl -O https://datasets.imdbws.com/title.basics.tsv.gz
curl -O https://datasets.imdbws.com/title.ratings.tsv.gz
curl -O https://datasets.imdbws.com/title.crew.tsv.gz
curl -0 https://datasets.imdbws.com/name.basics.tsv.gz

# Extract the downloaded .gz files
tar -xvzf title.basics.tsv.gz
tar -xvzf title.ratings.tsv.gz
tar -xvzf title.crew.tsv.gz
tar -xvzf name.basics.tsv.gz