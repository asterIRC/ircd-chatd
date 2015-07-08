/*
 *  ircd-ratbox: A slightly useful ircd.
 *  m_motd.c: Shows the current message of the day.
 *
 *  Copyright (C) 1990 Jarkko Oikarinen and University of Oulu, Co Center
 *  Copyright (C) 1996-2002 Hybrid Development Team
 *  Copyright (C) 2002-2005 ircd-ratbox development team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 *
 */

#include "stdinc.h"
#include "client.h"
#include "ircd.h"
#include "send.h"
#include "numeric.h"
#include "hook.h"
#include "msg.h"
#include "s_serv.h"		/* hunt_server */
#include "parse.h"
#include "modules.h"
#include "s_conf.h"
#include "cache.h"

static int m_rules(struct Client *, struct Client *, int, const char **);
static int mo_rules(struct Client *, struct Client *, int, const char **);

struct Message rules_msgtab = {
	"RULES", 0, 0, 0, MFLG_SLOW,
	{mg_unreg, {m_rules, 0}, {mo_rules, 0}, mg_ignore, mg_ignore, {mo_rules, 0}}
};

int doing_rules_hook;

mapi_clist_av1 rules_clist[] = { &rules_msgtab, NULL };
mapi_hlist_av1 rules_hlist[] = {
        { "doing_rules", &doing_rules_hook },
        { NULL, NULL }
};


DECLARE_MODULE_AV1(rules, NULL, NULL, rules_clist, rules_hlist, NULL, "$Revision: 254 $");

/*
** m_rules
**      parv[1] = servername
*/
static int
m_rules(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	static time_t last_used = 0;

	if((last_used + ConfigFileEntry.pace_wait) > rb_current_time())
	{
		/* safe enough to give this on a local connect only */
		sendto_one(source_p, form_str(RPL_LOAD2HI),
			   me.name, source_p->name, "MOTD");
		sendto_one(source_p, form_str(RPL_ENDOFMOTD),
			   me.name, source_p->name);
		return 0;
	}
	else
		last_used = rb_current_time();

	if(hunt_server(client_p, source_p, ":%s RULES :%s", 1, parc, parv) != HUNTED_ISME)
		return 0;

	send_user_rules(source_p);

	return 0;
}

/*
** mo_rules
**      parv[1] = servername
*/
static int
mo_rules(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(hunt_server(client_p, source_p, ":%s RULES :%s", 1, parc, parv) != HUNTED_ISME)
		return 0;

	send_user_rules(source_p);

	return 0;
}
