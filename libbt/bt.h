enum {
	TASKFRESH	= 0,
	TASKRUNNING,
	TASKFAIL,
	TASKSUCCESS,
	TASKMAX,
};

extern char *btstatenames[TASKMAX];

/* BehaviorAction is a leaf function.
 *
 * ctx - per-leaf context
 * v - data passed to bttick
 */
typedef int (*BehaviorAction)(void *ctx, void *v);

typedef struct Behavior Behavior;
#pragma incomplete Behavior

typedef struct BehaviorState BehaviorState;
#pragma incomplete BehaviorState

typedef struct BehaviorNode BehaviorNode;
#pragma incomplete BehaviorNode

Behavior *btnew();
Behavior *btroot(BehaviorNode *root);
BehaviorState *btstatenew(Behavior*);
void btstatefree(BehaviorState*, void *agent);

/* btleaf creates a new BehaviorNode leaf.
 *
 * name - string name, used for debugging
 * action - BehaviorAction function called when ticked
 * ctx - per-leaf context passed to action
 */
BehaviorNode *btleaf(char *name, BehaviorAction action, void *ctx);

/* control flow */
BehaviorNode *btsequence(char*, ...);
BehaviorNode *btpriority(char*, ...);
BehaviorNode *btparallel(char*, int, int, ...);
BehaviorNode *btdynguard(char*, ...);

/* add child to one of the above */
int btaddbranch(BehaviorNode*, BehaviorNode*);

/* decorators */
BehaviorNode *btinvert(char*, BehaviorNode*);

/* set guard function for node */
void btsetguard(BehaviorNode*, BehaviorNode*);

/* set end function for a node */
void btsetend(BehaviorNode*, void (*)(void*));

void btfreenode(BehaviorNode*);
void btfree(Behavior*);
int bttick(Behavior*, BehaviorState*, void*);

/* %T */
int btfmt(Fmt *f);

