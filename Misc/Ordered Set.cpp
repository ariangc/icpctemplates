#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef
tree<
	int,
	null_type,
	less<int>,
	rb_tree_tag,
	tree_order_statistics_node_update
>ordered_set;
// ordered_set
// X.find_by_order(k) returns an iterator to the k-th largest element (counting from zero)
// X.order_of_key(v) returns the number of items in a set that are strictly smaller than v
int main() {
	int N;
	ordered_set Y;
	Y.insert(5);
	trace (*Y.find_by_order(0));
}
