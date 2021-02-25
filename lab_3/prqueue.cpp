#include "prqueue.hpp"

bool PrQueue::isEmpty() const
{
    return vec_.size() == 0;
}

/* Item is a compound structure,
 * thus we receive it as a constant reference.
 * (We don't want to change it, only to add it to the queue,
 *  so the const keyword is fine here.)
 */
void PrQueue::add(const Item& e)
{
    vec_.push_back(e);
}

int PrQueue::maxIndex() const
{
    /* Maximum selection theorem.
     * The methods and functions that call this method have to make
     * sure that this is only called for non-empty priority queues.
     */
    int maxim = vec_[0].priority;
    int ind = 0;
    for (int i = 1; i < int(vec_.size()); ++i) {
        if (vec_[i].priority > maxim) {
            maxim = vec_[i].priority;
            ind = i;
        }
    }
    return ind;
}

Item PrQueue::remMax()
{
    /* If our priority queue is empty,
     * we cannot take out a maximal element from it,
     * thus we should throw an EMPTY PRQUEUE error (exception).
     * (In reality this is an integer, as the values of enum
     *  elements are mapped to integers.)
     */
    if (vec_.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex(); /// We select the index of the maximal element.
    Item e = vec_[ind]; /// We take out the maximal element.
    vec_[ind] = vec_.back(); /// We overwrite the maximal element with the last element of the vector.
    vec_.pop_back(); /// We remove the last element of the vector.
    return e;
}

Item PrQueue::getMax() const
{
    /* See remMax. The only difference
     * is that we do not remove the maximal element here,
     * we only query it (hence the const keyword).
     */
    if (vec_.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex();
    Item e = vec_[ind];
    return e;
}
