// 2D segment tree built from a lazy-init outer segment
// tree and a dynamic pb_ds inner segment tree.
// Requires tri = pair<ii,ll>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class Node_CItr,class Node_Itr, 
			class Cmp_Fn,class _Alloc>
struct my_update_policy
{
  virtual Node_CItr node_begin() const=0;
  virtual Node_CItr node_end() const=0;
  typedef ll metadata_type;
 
  ll prefix_sum(int y)
  {
		ll ans=0;
		auto it=node_begin();
		while(it!=node_end())
		{
			 auto l=it.get_l_child();
			 auto r=it.get_r_child();
			 if (y < (*it)->itm1) it=l;
			 else
			 {
				  ans+=(*it)->itm3;
				  if(l!=node_end()) ans+=l.get_metadata();
				  it=r;
			 }
		}
		return ans;
  }

  ll range_sum(int yl, int yr){ // sum in [l,r)
	 return prefix_sum(yr-1) - prefix_sum(yl-1);
  }
	
  // To update, remove node and add it with new value
  void operator()(Node_Itr it, Node_CItr end_it)
  {
		auto l=it.get_l_child();
		auto r=it.get_r_child();
		ll left=0,right=0;
		if(l!=end_it) left=l.get_metadata();
		if(r!=end_it) right=r.get_metadata();
		const_cast<ll&>(it.get_metadata()) = 
			(left+(*it)->itm3+right);
  }
};
     
typedef tree<tri,null_type,less<tri>,rb_tree_tag,
	my_update_policy> yseg; // (y, x, val)

const int MAX = 1e9;
const ll OpId = 0;
typedef yseg T;

struct node {
	T val;
	map<ii, ll> mk;
	node *l, *r;
	node() : l(NULL), r(NULL) { }
};

ll query(node* u, int xlo, int xhi, int ylo, int yhi, 
			int l = -MAX, int r = MAX){
	if (!u || r <= xlo || l >= xhi) return OpId;
	if (l >= xlo && r <= xhi) {
		return u->val.range_sum(ylo,yhi);
	}
	int m = (l+r)/2;
	return query(u->l, xlo, xhi, ylo, yhi, l, m) + 
			 query(u->r, xlo, xhi, ylo, yhi, m, r);
}

node* update(node* u, int px, int py, ll x, 
				 int l = -MAX, int r = MAX){ // [l,r)
	if (l > px || r <= px) return u;
	if (!u) u = new node(); // For persistent remove if
	if (l+1 == r) {
		u->val.clear();
		u->val.insert(mt(py,px,x));
		return u;
	}
	int m = (l+r)/2;
	u->l = update(u->l, px, py, x, l, m);
	u->r = update(u->r, px, py, x, m, r);
	if (u->mk.count(mp(px,py))) 
		u->val.erase(mt(px,py, u->mk[mp(px,py)]));
	u->mk[mp(px,py)] = x;
	u->val.insert(mt(px,py,x));
	return u;
}
