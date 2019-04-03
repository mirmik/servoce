"""
Минимальная реализация решателя задачи инверсной кинематики.
"""

import numpy


class vec3:
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

    def normalize(self):
        a = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
        return vec3(self.x / a, self.y / a, self.z / a)


class quat:
    def __init__(self, x, y, z, w):
        self.x, self.y, self.z, self.w = x, y, z, w

    def normalize(self):
        a = math.sqrt(
            self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w
        )
        return quat(self.x / a, self.y / a, self.z / a, self.w / a)


def rotation_quat(ax, angle):
    s = math.sin(angle / 2)
    c = math.cos(angle / 2)
    return quat(s * ax.x, s * ax.y, s * ax.z, c)


def qrot(q, v):
    ww = q.w * q.w
    xx = q.x * q.x
    yy = q.y * q.y
    zz = q.z * q.z
    wx = q.w * q.x
    wy = q.w * q.y
    wz = q.w * q.z
    xy = q.x * q.y
    xz = q.x * q.z
    yz = q.y * q.z

    return vec(
        v.x * (ww + xx - yy - zz) + v.y * (xy - wz) * 2 + v.z * (xz + wy) * 2,
        v.x * (xy + wz) * 2 + v.y * (ww - xx + yy - zz) + v.z * (yz + wx) * 2,
        v.x * (xz - wy) * 2 + v.y * (yz - wx) * 2 + v.z * (ww - xx - yy + zz),
    )


class mtrans:
    def __init__(self, rot, mov):
        self.rot = rot
        self.mov = mov

    def __mul__(self, oth):
        return mtrans(self.rot * oth.rot, qrot(self.rot, oth.mov) + self.mov)

    @static
    def rotation(axis, angle):
        return mtrans(rotation_quat(axis, angle), vec3(0, 0, 0))

    @static
    def translation(v):
        return mtrans(quat(0, 0, 0, 1), v)


# 	def normalize(self):
# 		pass


class spdbivec3:
    def __init__(self, w, v):
        self.w = w
        self.v = v

    def transform(self, trans):
        res_w = trans.rotate(w)
        res_v = trans.rotate(cross(self.w, trans.mov) + self.v)
        return spdbivec3(res_w, res_v)


class abstract_link:
    def __init__(self):
        pass


class constant_link(abstract_link):
    dim = 0

    def __init__(self, tr):
        self.trans = tr

    def get_trans(self):
        return self.trans


class rotate_link(abstract_link):
    dim = 1

    def __init__(self, ax):
        self.ax = vec(*ax)

    def get_trans(self, coord):
        """Получить объект локальной трансформации"""
        return mtrans.rotation(self.ax, coord)

    def d1(self):
        """Получить 6-вектор, описывающей мгновенную производную положения
		по управляющей координате [w,v]."""
        return spdbivec3(vec3(self.x, self.y, self.z), vec3(0, 0, 0))


class translate_link(abstract_link):
    dim = 1

    def __init__(self, ax):
        self.ax = vec(*ax)

    def get_trans(self, coord):
        """Получить объект локальной трансформации"""
        return mtrans.translation(self.ax)

    def d1(self):
        """Получить 6-вектор, описывающей мгновенную производную положения
		по управляющей координате [v,w]."""
        return spdbivec3(vec3(0, 0, 0), vec3(self.x, self.y, self.z))


class chain:
    def __init__(self, links):
        self.links = simplify_chain(links)

        self.ndim = 0
        for l in self.links:
            self.ndim += l.dim

    def simplify_chain(self):
        pass

    def speed_transes(self, coords):
        """Алгоритм возвращает бивектор мгновенных скоростей выходного звена приведенных к возможным обобщенным скоростям"""

        assert len(coords) == self.ndim

        ret = []
        curtrans = mtrans.identity()
        coordpos = len(coords)

        for index in xrange(len(coords) - 1, -1, -1):
            """Обходим лист с обратной стороны"""
            l = self.links[index]

            if l.dim > 0:
                if l.dim == 1:
                    ret.append(l.d1().transform(curtrans.invert()))
                    coord = coords[coordpos]
                    coordpos -= 1
                    ltrans = l.get_trans(coord)

                else:
                    raise ValueError("TODO")

            else:
                ltrans = l.get_trans()

            curtrans = ltrans * curtrans

        return ret
