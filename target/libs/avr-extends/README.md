# avr-extends

Extensions to the avr MCU library provided by avr-gcc. The avr-gcc c-lib is very
limited and thus wrappers are needed for more complex functionality UART etc.

## Architecture

This library uses cmake and just requires the inclusion of:

```python
target_link_libraries(<exe-name> PRIVATE avr-extends)
```

and

```python
add_subdirectory(libs/avr-extends)
```

See [embedded-terminal](https://github.com/jaxsonpd/embedded-terminal) or [flight-sim-software](https://github.com/jaxsonpd/flight-sim-software) for an example of this in action.

## Installation and git submodules

This library is designed to work as a git submodule as part of a larger project.

Add the library to the git project using:

```bash
git submodule add https://github.com/jaxsonpd/avr-extends avr-extends
```

If cloning a repository with the submodule already installed use:

```bash
git clone --recursive <project url>
```

To update the submodule from the parent repository:

```bash
git submodule update --remote
```

or

```bash
git pull --recurse-submodules
```

> [WARNING]
> This will overwrite local changes (which can be recovered by switching back to local branch)

### Working on a submodule

Submodules have no local branch the head is in a detached state so a branch must
be checked out before work can be done (from inside the submodule repository).

To stop the local changes from being overwritten use:

```bash
git submodule update --remote --merge
```

Where the `--merge` is what keeps the local branch and can use `--rebase` aswell.

To push changes use:

```bash
git push --recurse-submodules=check
```

This is import to maintain the link to the correct commit of the submodule by
the parent directory.
