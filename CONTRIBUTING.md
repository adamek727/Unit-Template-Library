# Contributing

## Git history rule: one PR, one commit on `main`

`main` is a linear history with **exactly one commit per pull request**. There
are no merge commits and no intermediate "WIP" / "fix typo" / "address review"
commits on `main`.

- **Every change lands through a PR.** Do not commit directly to `main`.
- **PRs are squash-merged only.** The repository is configured to allow squash
  merges exclusively (merge commits and rebase merges are disabled, and the
  source branch is deleted on merge). The squash commit takes the PR title and
  body, so write those as the final commit message.
- **One concern per PR.** A PR is a single feature, fix, or chore — not several
  unrelated changes bundled together. Split unrelated work into separate PRs.
- **Keep branches rebased on `main`.** Resolve conflicts on your branch before
  merging; never merge `main` back into the branch.

### Commit message format

Squash commit subjects follow [Conventional Commits](https://www.conventionalcommits.org):

```
<type>: <imperative summary>
```

`type` is one of `feat`, `fix`, `refactor`, `perf`, `test`, `build`, `ci`,
`docs`, `chore`. Append `!` (e.g. `feat!:`) for a breaking change and record it
in `CHANGELOG.md`. Use the body to explain *why*, not *what*.

## Before opening a PR

Mirror CI locally; all of these must pass (CI treats warnings as errors):

```bash
cmake -B build -DENABLE_TESTS=1 -DENABLE_EXAMPLES=1 -DENABLE_WERROR=1
cmake --build build -j
ctest --test-dir build --output-on-failure
clang-format --dry-run --Werror $(find include tests examples \( -name '*.hpp' -o -name '*.cpp' \))
python3 tools/check_zero_overhead.py g++   # and clang++
```

New behaviour is defined test-first (TDD); for compile-time API the failing
"red" state is a compilation error. See `CLAUDE.md` for architecture and the
MSVC/portability conventions, and `FUTURE_WORK.md` for the roadmap.
