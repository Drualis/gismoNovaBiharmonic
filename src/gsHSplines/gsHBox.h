/** @file gsHBox.h

    @brief Provides definition of the gsHBox

    This file is part of the G+Smo library.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    Author(s): G. Kiss, A. Mantzaflaris, J. Speh
*/

#pragma once

#include <gsHSplines/gsHBoxUtils.h>
#include <gsHSplines/gsHDomainIterator.h>
#include <gsHSplines/gsHTensorBasis.h>
#include <gsIO/gsXml.h>

namespace gismo
{

template<int d, class T>
class gsHBox
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

public:
    typedef gsVector<index_t,d> point;
    typedef typename Eigen::aligned_allocator<gsHBox<d,T>> aalloc;

    typedef typename std::vector<index_t>                                   RefBox;
    typedef typename std::list<gsHBox<d,T>,typename gsHBox<d,T>::aalloc>    Container;
    typedef typename std::vector<gsHBox<d,T>,typename gsHBox<d,T>::aalloc>  SortedContainer;
    typedef typename std::vector<Container>                                 HContainer; // container[level]
    typedef typename Container::iterator            Iterator;
    typedef typename Container::reverse_iterator    rIterator;
    typedef typename Container::const_iterator      cIterator;
    typedef typename HContainer::iterator           HIterator;
    typedef typename HContainer::reverse_iterator   rHIterator;
    typedef typename HContainer::const_iterator     cHIterator;


public:

    gsHBox();

    gsHBox(const gsHDomainIterator<T,d> * domHIt);

    gsHBox(const gsHDomainIterator<T,d> * domHIt, const index_t pid);

    gsHBox(const typename gsHBox<d,T>::point & low,const typename gsHBox<d,T>::point & upp, index_t level, const gsHTensorBasis<d,T> * basis, const index_t pid = -1);

    gsHBox(const gsAabb<d,index_t> & box, const gsHTensorBasis<d,T> * basis, const index_t pid = -1);

    gsHBox(const std::vector<index_t> & indices, const gsHTensorBasis<d,T> * basis, const index_t pid = -1);

    /// Copy constructor (makes deep copy)
    gsHBox( const gsHBox<d,T> & other );

    /// Move constructor
    gsHBox( gsHBox<d,T> && other );

    /// Assignment operator
    gsHBox<d,T> & operator= ( const gsHBox<d,T> & other );

    /// Move assignment operator
    gsHBox<d,T> & operator= ( gsHBox<d,T> && other );

    /**
     * @brief      Checks if the \a other cell is contained in \a this cell
     *
     * @param      other  The other cell
     *
     * @return     True if the specified other is contained in the cell, False otherwise.
     */
    bool isContained(const gsHBox<d,T> & other) const;

    /**
     * @brief      Checks if the \a other cell is contains in \a this cell
     *
     * @param      other  The other cell
     *
     * @return     True if the specified other is contains in the cell, False otherwise.
     */
    bool contains(const gsHBox<d,T> & other) const;

    /**
     * @brief      Determines whether the \a this box is the same as the \a other box
     *
     * @param[in]  other  The other box
     *
     * @return     True if the boxes are the same, False otherwise.
     */
    bool isSame(const gsHBox<d,T> & other) const;

    /**
     * @brief      Determines if the box is active on its current level.
     *
     * @return     True if active, False otherwise.
     */
    bool isActive() const;

    /**
     * @brief      Determines if active or contained in the active elemebt.
     *             In other words; checks if the level of this box is higher or equal to the level of the mesh here.
     *
     * @return     True if active or contained, False otherwise.
     */
    bool isActiveOrContained() const;

    /**
     * @brief      Gets the coordinates of the box (first column lower corner, second column higher corner).
     *
     * @return     The coordinates of the box.
     */
    const gsMatrix<T> & getCoordinates() const;

    /**
     * @brief      Gets the center of the box.
     *
     * @return     The center of the box.
     */
    const gsMatrix<T> & getCenter() const;

    /**
     * @brief      Gets the lower corner of the box
     *
     * @return     The lower corner
     */
    gsVector<T,d> lowerCorner() const;

    /**
     * @brief      Gets the upper corner of the box
     *
     * @return     The upper corner
     */
    gsVector<T,d> upperCorner() const;

    /// Return the diagonal of the element
    T getCellSize() const;

    /// Return the length of the smallest edge of the element
    T getMinCellLength() const;

    /// Return the length of the largest edge of the element
    T getMaxCellLength() const;

    /**
     * @brief      Gets the lower index of the box
     *
     * @return     The lower index
     */
    const point & lowerIndex() const;
    /**
     * @brief      Gets the upper index of the box
     *
     * @return     The upper index
     */
    const point & upperIndex() const;

    /**
     * @brief      Gets the patch ID of the object
     *
     * @return     The patch ID of the object
     */
    index_t patch() const;

    /**
     * @brief      Gets the level of the object
     *
     * @return     The level of the object
     */
    index_t level() const;

    /**
     * @brief      Gets the level in the center of the object
     *
     * @return     The level in the center of the object
     */
    index_t levelInCenter() const;

    /**
     * @brief      Sets the error of the object
     */
    void setError(T error);

    /**
     * @brief      Sets the error of the object and compute the projection of the error on a finer mesh
     */
    void setAndProjectError(T error);

    /**
     * @brief      Gets the error stored in the object
     *
     * @return     The error of the object
     */
    T error() const;

    /**
     * @brief      Gets the projected error stored in the object
     *
     * @return     The error of the object
     */
    T projectedError() const;

    /**
     * @brief      Gets the projected improvement = error - projected error
     *
     * @return     The projected improvement
     */
    T projectedImprovement() const;

    /**
     * @brief      Assigns an index to the object
     */
    void setIndex(index_t index);

    /**
     * @brief      Gets the index stored in the object
     *
     * @return     The index of the object
     */
    index_t index() const;

    /**
     * @brief      Marks \a this element for refinement
     */
    void mark();
    /**
     * @brief      Unmarks \a this element for refinement
     */
    void unmark();

    /**
     * @brief      Returns whether the element is marked or not
     *
     * @return     \a this is marked
     */
    bool marked() const;

    /**
     * @brief      Sets the mark.
     *
     * @param[in]  mark  The mark
     */
    void setMark(bool mark);

    /**
     * @brief      Gets the parent of the object.
     *
     * @return     The parent of the object.
     */
    gsHBox<d,T> getParent() const;

    /**
     * @brief      Gets the ancestor of the object on level \a k.
     *
     * @param[in]  k     The reference level
     *
     * @return     The ancestor.
     */
    gsHBox<d,T> getAncestor(index_t k) const;

    /**
     * @brief      Gets the children of the object.
     *
     * @return     The children of the object.
     */
    Container getChildren() const;

    /**
     * @brief      Gets the descendants of the object on level \a k.
     *
     * @param[in]  k     The reference level
     *
     * @return     The children of the object.
     */
    Container getDescendants(index_t k) const;

    /**

     */
    Container getSiblings() const;

    /**
     * @brief      Gets the support extension.
     *
     * @return     The support extension.
     */
    Container getSupportExtension();

    /**
     * @brief      Gets the multi-level support extension.
     *
     * @param[in]  k     The reference level
     *
     * @return     The multi-level support extension.
     */
    Container getMultiLevelSupportExtension(index_t k);

    /**
     * @brief      Gets the H-neighborhood.
     *
     * @param[in]  m     The jump parameter
     *
     * @return     The H-neighborhood.
     */
    Container getHneighborhood(index_t m);

    /**
     * @brief      Gets the T-neighborhood.
     *
     * @param[in]  m     The jump parameter
     *
     * @return     The T-neighborhood.
     */
    Container getTneighborhood(index_t m);


    /**
     * @brief      Gets the neighborhood.
     *
     * @param[in]  m     The jump parameter
     *
     * @tparam     _mode  H or T refinement (else not implemented)
     *
     * @return     The neighborhood.
     */
    template<enum Neighborhood _mode>
    typename gsHBox<d,T>::Container getNeighborhood(index_t m) { return getNeighborhood_impl<_mode>(m);}


    /**
     * @brief      Gets the refinement neighborhood.
     * Returns either the H- or T-neighborhood, depending on the underlying basis
     *
     * @param[in]  m     The jump parameter
     *
     * @return     The T-neighborhood.
    */
    Container getNeighborhood(index_t m);

    /**
     * @brief      Gets the Coarsening neighborhood.
     *
     * @param[in]  m     The jump parameter
     *
     * @return     The coarsening neighborhood.
     */
    Container getCneighborhood(index_t m);

    /**
     * @brief      Gets the Coarsening extension,
     * which is the coarsening neighborhood before checking for active elements.
     *
     * @param[in]  m     The jump parameter
     *
     * @return     The coarsening extension.
     */
    Container getCextension(index_t m);

    /**
     * @brief      Returns a container representation of the object.
     *
     * @return     Container representation of the object.
     */
    Container            toContainer();

    /**
     * @brief      Returns a hierarchical container representation of the object.
     *
     * @return     Hierarchical container representation of the object.
     */
    HContainer           toHContainer();

    /**
     * @brief      Prints the object
     *
     */
    std::ostream& print( std::ostream& os ) const;

    /**
     * @brief      Returns a box representation of the object
     *
     * @return     Box representation of the object.
     */
    RefBox toBox() const;

    /**
     * @brief      Returns a box representation of the object on the lower level (needed for refinement).
     *
     * @return     Refinement box representation of the object.
     */
    RefBox toRefBox(index_t targetLevel) const;
    RefBox toRefBox() const
    {
        return this->toRefBox(this->level()+1);
    }

    /**
     * @brief      Returns a box representation of the object on the higher level (needed for coarsening).
     *
     * @return     Coarsening box representation of the object.
     */
    RefBox toCrsBox(index_t targetLevel) const;
    RefBox toCrsBox() const
    {
        return this->toCrsBox(this->level()-1);
    }

    // Helper functions
    HContainer           boxUnion(const HContainer & container1, const HContainer & container2) const;

    const gsHTensorBasis<d,T> & basis() const { return *m_basis; }

    /**
     * @brief      Returns unit boxes representation of the object.
     *
     * @return     Unit boxes representation of the object.
     */
    Container toUnitBoxes() const;

    /**
     * @brief      Checks if the box has positive indices
     *
     * @return     True if the box has positive indices, false otherwise
     */
    bool good() const;

    /**
     * @brief      Cleans the container from bad elements (see \a good())
     *
     * @param      container  The container
     */
    void clean(Container & container) const;

    /**
     * @brief      Computes the parametric coordinates of \a this
     */
    void computeCoordinates() const;
    /**
     * @brief      Computes the center of \a this
     */
    void computeCenter() const;

protected:

    void _computeIndices();
    gsAabb<d,index_t> _computeIndices(const gsMatrix<T> & coords, index_t level);
    gsAabb<d,index_t> _computeIndices(const gsMatrix<T> & coords, const gsMatrix<T> & center);
    gsAabb<d,index_t> _computeIndices(const gsMatrix<T> & coords);

    gsAabb<d,index_t> _elevateBox(const gsAabb<d,index_t> & box) const;
    gsAabb<d,index_t> _lowerBox(const gsAabb<d,index_t> & box) const;

    Container  _getParents(typename gsHBox<d,T>::Container  & container) const;
    HContainer _getParents(typename gsHBox<d,T>::HContainer & container) const;


    Container _boxUnion(const Container & container1, const Container & container2) const;
    Container _makeUnique(const Container & container) const;

    template<enum Neighborhood _mode>
    typename std::enable_if<_mode==Neighborhood::Automatic, typename gsHBox<d,T>::Container>::type
    getNeighborhood_impl(index_t m)
    {
        return this->getNeighborhood(m);
    }

    template<enum Neighborhood _mode>
    typename std::enable_if<_mode==Neighborhood::T, typename gsHBox<d,T>::Container>::type
    getNeighborhood_impl(index_t m)
    {
        return this->getTneighborhood(m);
    }

    template<enum Neighborhood _mode>
    typename std::enable_if<_mode==Neighborhood::H, typename gsHBox<d,T>::Container>::type
    getNeighborhood_impl(index_t m)
    {
        return this->getHneighborhood(m);
    }


protected:
    gsAabb<d,index_t> m_indices;

    index_t m_pid;
    mutable gsMatrix<T> m_coords;
    mutable gsMatrix<T> m_center;
    const gsHTensorBasis<d,T> * m_basis;

    T m_error;
    T m_error_proj;
    index_t m_index;
    bool m_marked;

}; // class gsHBox


template<int d, class T>
std::ostream& operator<<( std::ostream& os, const gsHBox<d,T>& b )
{
    return b.print( os );
}

} // namespace gismo

// *****************************************************************
#ifndef GISMO_BUILD_LIB
#include GISMO_HPP_HEADER(gsHBox.hpp)
#else
#ifdef gsHBox_EXPORT
#include GISMO_HPP_HEADER(gsHBox.hpp)
#undef  EXTERN_CLASS_TEMPLATE
#define EXTERN_CLASS_TEMPLATE CLASS_TEMPLATE_INST
#endif
namespace gismo
{
EXTERN_CLASS_TEMPLATE gsHBox<1,real_t>;
EXTERN_CLASS_TEMPLATE gsHBox<2,real_t>;
EXTERN_CLASS_TEMPLATE gsHBox<3,real_t>;
EXTERN_CLASS_TEMPLATE gsHBox<4,real_t>;

EXTERN_CLASS_TEMPLATE internal::gsXml< gsHBox<1,real_t> >;
EXTERN_CLASS_TEMPLATE internal::gsXml< gsHBox<2,real_t> >;
EXTERN_CLASS_TEMPLATE internal::gsXml< gsHBox<3,real_t> >;
EXTERN_CLASS_TEMPLATE internal::gsXml< gsHBox<4,real_t> >;

}
#endif
// *****************************************************************
