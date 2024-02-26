# Slobodni vektori

## 🎓 Autori

- [Marko Gordić](https://github.com/MarkoGordic) - IN 37/2023
- [Nađa Jakšić](https://github.com/nadjaaaj) - IN 33/2023
- [Igor Maljik](https://github.com/IgorMaljik) - SV 37/2023

## 📜 Teorija

- Skup svih klasa, tj. slobodnih vektora, obeležavaće se sa $V$.

- Vektor je skup svih orijentisanih duži "strlica" koje su međusobno podudarne, paralelne i isto orijentisane. Vektor je takođe duž "strlica" koja, kada se pomeri paralelno samoj sebi, predstavlja isti vektor.

- **Ort** je jedinični vektor (intenzitet mu je 1).

- Dva vektora $\vec{a}$ i $\vec{b}$ su **kolinearna** ako i samo ako imaju isti pravac, tj. ako postoji skalar $\alpha \in \mathbb{R} \setminus \{0\}$ takav da je $\vec{a} = \alpha \vec{b}$.

- Dva vekotra su **paralelna** ako im je **vektorski proizvod 0**.

- Dva vektora su **ortogonalna** (**normalna**) ako im je **skalarni proizvod 0**.

- $(V,+)$ je Abelova grupa.

- Za sve vektore $\vec{x}$ i $\vec{n} \neq 0$ važi da je $\vec{x} - pr_{\vec{n}}(\vec{x}) \bot \vec{n}$

Za svaka 2 nekolinearna vektora $\vec{a}$ i $\vec{b}$ važi $\quad \alpha\vec{a} + \beta\vec{b} = 0 \quad \Rightarrow \quad \alpha = \beta = 0$

## Skalarni proizvod vektora (skalar)

$\vec{a} \cdot \vec{b} = |\vec{a}| \cdot |\vec{b}| \cdot \cos \angle {(\vec{a}, \vec{b})}$

### Osobine:

1) $\vec{a} \cdot \vec{a} = |\vec{a}|^2\quad\Leftrightarrow\quad |\vec{a}| = \sqrt{\vec{a} \cdot \vec{a}}$

2) $\vec{a} \perp \vec{b} \Leftrightarrow \vec{a} \cdot \vec{b} = 0$

3) $\vec{a} = (a_1,a_2,a_3), \vec{b} = (b_1,b_2,b_3) \Rightarrow \vec{a} \cdot \vec{b} = a_1b_1 + a_2b_2 + a_3b_3$

4) $|\vec{a}| = \sqrt{a_1^2 + a_2^2 + a_3^2}$

## Vektorski proizvod (vektor)

$(\vec{a} \times \vec{b}) \perp \vec{a} \quad\land\quad (\vec{a} \times \vec{b}) \perp \vec{b}$

$|\vec{a} \times \vec{b}| = |\vec{a}||\vec{b}||\sin\angle(\vec{a},\vec{b})|$ - površina paralelograma konstruisanog nad tim vektorima kao stranicama

$(\vec{a},\vec{b},\vec{a}\times\vec{b})$ - grade desni triedar

### Osobine:

1) $\vec{a} \times \vec{a} = \vec{0}$

2) $\vec{a} \times \vec{b} = -\vec{b} \times \vec{a}$

3) $\vec{a} \parallel \vec{b} \quad\Leftrightarrow\quad \vec{a} \times \vec{b} = 0$

4) $\alpha \cdot (\vec{a} \times \vec{b}) = \alpha\vec{a} \times \vec{b} = \vec{a} \times \alpha \vec{b}$

$\vec{a} = (a_1, a_2, a_3), \vec{b} = (b_1, b_2, b_3), \quad \vec{a} \times \vec{b} =
\begin{vmatrix}
\vec{i} & \vec{j} & \vec{k} \\
a_1 & a_2 & a_3 \\
b_1 & b_2 & b_3
\end{vmatrix}$

## Mešoviti proizvod

$[\vec{a},\vec{b},\vec{c}] = \vec{a} \cdot (\vec{b} \times \vec{c}) = 
\begin{vmatrix}
a_1 & a_2 & a_3 \\
b_1 & b_2 & b_3 \\
c_1 & c_2 & c_3
\end{vmatrix}$

$|[\vec{a},\vec{b},\vec{c}]|$ je zapremina paralelopipeda nad $\vec{a}, \vec{b}, \vec{c}$.

$\vec{a}, \vec{b}, \vec{c}$ su **komplanarni** (leže u istoj ravni) ako je mešoviti proizvod jednak nuli, $[\vec{a},\vec{b},\vec{c}] = 0$.

- Ako su tri vektora **komplanarna**, tada se kaže da su **linearno zavisni**. Kada su vektori linearno zavisni, tada su **kolinearni** ili **komplanarni**.

## Projekcija vektora $\vec{x}$ na pravac vektora $\vec{a}$

$pr_{\vec{a}}(\vec{x}) = |\vec{x}|\cos{\angle(\vec{a},\vec{x})} \cdot \frac{\vec{a}}{|\vec{a}|} = \frac{\vec{a}\vec{x}}{|\vec{a}|} \cdot \frac{\vec{a}}{|\vec{a}|} = \frac{\vec{a}\vec{x}}{|\vec{a}|^2} \vec{a}$  
Ova jednačina se dobija uklapanjem početne u jednačinu skalarnog proizvoda dva vektora.

Projekcija vektora $\vec{x}$ na pravac vektora $\vec{a}$ jeste vektor.

**Algebarska projekcija vektora** $\vec{x}$ na pravac vektora $\vec{a}$ je broj $\frac{\vec{a}\vec{x}}{|\vec{a}|}$

Svaka tačka A određuje neki vektor $\vec{OA}$, gde je $O$ koordinatni početak. Taj vektor se zove **vektor položaja** tačke $A$ i označava se sa $\vec{r}_A.

$A(x,y,z) \Rightarrow x\vec{i} + y\vec{j} + z\vec{k}$