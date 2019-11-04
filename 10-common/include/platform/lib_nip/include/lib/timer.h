/*
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _ZEBRA_TIMER_H
#define _ZEBRA_TIMER_H


typedef void (TIMER_FUNC)(void *para);
typedef    int      timer_lock;

#define TIMER_LOCK_INIT(t)     \
    (t)->lock = 0
#define TIMER_LOCK(t)   \
    (t)->lock = 1
#define TIMER_UNLOCK(t)     \
    (t)->lock = 0
#define TIMER_LOCK_TEST(t)  ((t)->lock)


typedef enum {
    TIMER_NEW = 0x800,
    TIMER_UPDATE,
    TIMER_REMOVE,
}TIMER_ACTION;

typedef struct _timer
{
    TIMER_FUNC  *func;
    void        *para;
    int          flags;
    time_t       timeout;
    int          deltime;
    timer_lock   lock;
}timer_handle;


#define TIMER_ONCE      0x00
#define TIMER_ALWAYS    0x01


int timer_remove(timer_handle* timer);
int timer_update(timer_handle* timer, int timeout);
timer_handle *timer_add(int timeout, TIMER_FUNC func, void *para, int flags);
int timer_init();



#endif
