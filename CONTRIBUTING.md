# CONTRIBUTING.md

## Commit Message Guidelines

A well-structured and informative commit message is essential for maintaining a clear and understandable version history of the codebase.
Below is the commit message template we will follow.

---

## Commit Format

```
<type>(<scope>): <subject>

[optional body]

[optional footer]
```

### Type (required)

The type of change describing the purpose of the commit:

| Type       | Description                                     |
| ---------- | ----------------------------------------------- |
| `feat`     | New feature for the user                        |
| `fix`      | Bug fix                                         |
| `docs`     | Documentation changes                           |
| `style`    | Code formatting (indentation, semicolons, etc.) |
| `refactor` | Code refactoring without behavior change        |
| `test`     | Adding or modifying tests                       |
| `chore`    | Routine tasks, maintenance, tooling changes     |

### Scope (optional)

Specifies the module, component, or functional area affected by the commit:

- `ui`
- `solver`
- `database`
- etc.

### Subject (required)

A short, imperative statement summarizing the change.

### Body (optional)

A more detailed description of the change, including the reason for it and possible side effects. Use this section to provide context.

### Footer (optional)

Additional information, such as issue references. You **must** use this section to reference relevant tickets.

---

## Examples

```
fix(solver): 0 angle velocity in Rolling
Redefinition of new, Rolling specific, functions from base
equipment class;
```

```
feat(api): add pagination support for listings

Implement pageable responses for GET /api/v1/listings
Add default sorting by creation date descending
Closes #123
```

```
docs(readme): update installation instructions
```

```
refactor(database): optimize user queries with join fetch
```
