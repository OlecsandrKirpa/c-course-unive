Il token è l'unità più piccola con cui abbiamo a che fare lavorando in C.

```c
int x = y + 3;
// This is a STATEMENT, è un'espressione.
```
| token | meaning |
| --- | --- |
| `int` | keyword |
| `x`, `y` | identifiers |
| `+`, `=` | operators |
| `3` | literal |
| `<space>`, `;` | separator |

Identifiers must start with a-z, A-Z or _.

### Operators
Operators are token that are used to perform an *operation*.

It could be:
- arithmetic: `+`, `-`
- logical: `||`, `&&`
- relational: `a < b`
- bitwise.

### Malloc