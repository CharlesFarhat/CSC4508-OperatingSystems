This project is a fork of the amazing project xv6 developed at MIT for the CSC4508 course given at TSP.
You can find the original README under the name README.

We explain in the remaining sections how we can synchronize this repository with the
repositories that contain the solutions, and with the repository of the mit.

# Clone the project, create the remotes and associate local branches to remote ones

```bash
# clone the repository
git clone ssh://git@gitlab.inf.telecom-sudparis.eu:2222/csc4508/xv6-tsp.git
cd xv6-tsp

# add the other remotes repositories
git remote add mit https://github.com/mit-pdos/xv6-public.git
git remote add scheduler-soluce ssh://git@gitlab.inf.telecom-sudparis.eu:2222/csc4508/xv6-soluces/xv6-soluce-scheduler.git
git remote add futex-soluce ssh://git@gitlab.inf.telecom-sudparis.eu:2222/csc4508/xv6-soluces/xv6-soluce-futex.git
git remote add shm-soluce ssh://git@gitlab.inf.telecom-sudparis.eu:2222/csc4508/xv6-soluces/xv6-soluce-shm.git
git remote add mmap-soluce ssh://git@gitlab.inf.telecom-sudparis.eu:2222/csc4508/xv6-soluces/xv6-soluce-mmap.git

# fetch all the repositories
git fetch --all

# create the local branches to track the remote branches
git checkout -b scheduler-lab -t origin/scheduler-lab
git checkout -b mit -t mit/master
git checkout -b scheduler-soluce -t scheduler-soluce/scheduler-lab
git checkout -b futex-soluce -t futex-soluce/master
git checkout -b shm-soluce -t shm-soluce/master
git checkout -b mmap-soluce-exo1 -t mmap-soluce/exo1
git checkout -b mmap-soluce-exo2 -t mmap-soluce/exo2
git checkout -b mmap-soluce-exo3 -t mmap-soluce/exo3

# make fetch and push symetric
git config push.default upstream

# switch to master
git checkout master
```

In order to check that everything is ok, just run `git branch -vv`: you will se which local branch
is associated to which remote branch.

# Rebasing

Rebasing an history pushed on a remote repository is not a good idea because it could break
what other developers are doing. However, in our case, since we are only few teachers,
we can, sometime, rebase our histories (even in the remotes).
Let's take an example: I made some modifications in master and I want to
rebase the other branches (instead of merging in order to avoid an ugly history):

```bash
git checkout scheduler-lab
git rebase master
git push --force                    # because we modify the history of a remote

git checkout scheduler-soluce
git rebase scheduler-lab
git push --force                    # because we modify the history of a remote

git checkout futex-soluce
git rebase master
git push --force                    # because we modify the history of a remote

# etc.... for all the branches
```

