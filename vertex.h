#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

class Vertex
{
public:
    // Constructors
    Q_DECL_CONSTEXPR Vertex();
    Q_DECL_CONSTEXPR explicit Vertex(const QVector3D &position);
    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color);
    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector2D &texCoord, const QVector3D &normal);

    // Accessors / Mutators
    Q_DECL_CONSTEXPR const QVector3D& position() const;
    Q_DECL_CONSTEXPR const QVector3D& normal() const;
    Q_DECL_CONSTEXPR const QVector2D& texCoord() const;
    void setPosition(const QVector3D& position);
    void setNormal(const QVector3D& normal);
    void setTexCoord(const QVector2D& texCoord);
    void setTangent(const QVector3D& tangent);

    void addTangent(const QVector3D& tangent);
    void normalizeTangent();

    // OpenGL Helpers
    static const int PositionTupleSize = 3;
    static const int NormalTupleSize = 3;
    static const int TexCoordTupleSize = 2;
    static const int TangentTupleSize = 3;
    static Q_DECL_CONSTEXPR int texCoordOffset();
    static Q_DECL_CONSTEXPR int positionOffset();
    static Q_DECL_CONSTEXPR int normalOffset();
    static Q_DECL_CONSTEXPR int tangentOffset();
    static Q_DECL_CONSTEXPR int stride();

private:
    QVector3D m_position;
    QVector3D m_normal;
    QVector2D m_texCoord;
    QVector3D m_tangent;// = QVector3D(0.0f, 0.0f, 0.0f);
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

// Constructors
Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position) : m_position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector3D &normal) : m_position(position), m_normal(normal) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector2D &texCoord, const QVector3D &normal)
    : m_position(position), m_normal(normal), m_texCoord(texCoord) {}

// Accessors / Mutators
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::position() const { return m_position; }
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::normal() const { return m_normal; }
Q_DECL_CONSTEXPR inline const QVector2D& Vertex::texCoord() const { return m_texCoord; }
void inline Vertex::setPosition(const QVector3D& position) { m_position = position; }
void inline Vertex::setTexCoord(const QVector2D& texCoord) { m_texCoord = texCoord; }
void inline Vertex::setNormal(const QVector3D& normal) { m_normal = normal; }
void inline Vertex::setTangent(const QVector3D &tangent) { m_tangent = tangent; }

void inline Vertex::addTangent(const QVector3D &tangent) { m_tangent += tangent; }

void inline Vertex::normalizeTangent() { m_tangent.normalize(); }

// OFFSETT
Q_DECL_CONSTEXPR inline int Vertex::positionOffset() { return offsetof(Vertex, m_position); }
Q_DECL_CONSTEXPR inline int Vertex::normalOffset() { return offsetof(Vertex, m_normal); }
Q_DECL_CONSTEXPR inline int Vertex::texCoordOffset() { return offsetof(Vertex, m_texCoord); }
Q_DECL_CONSTEXPR inline int Vertex::tangentOffset() { return offsetof(Vertex, m_tangent); }

Q_DECL_CONSTEXPR inline int Vertex::stride() { return sizeof(Vertex); }

#endif // VERTEX_H
