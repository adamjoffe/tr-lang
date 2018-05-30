#ifndef TR_ATTACHABLE_H
#define TR_ATTACHABLE_H

#include "../AST/abstract_visitor.h"
#include "../exe-components/exit_tr.h"

namespace TR {

	class TRAttachable {

	public:

		/**
		 * Attachable action at start of node
		 *
		 * Does action at start of AST nodes 
		 *
		 * @param ast Node to do start action with
		 */
        virtual void start_node(ASTNode* ast) = 0;

		/**
		 * Attachable action at end of node
		 *
		 * Does action at end of AST nodes 
		 *
		 * @param ast Node to do end action with
		 */
        virtual void end_node(ASTNode* ast) = 0;

		/**
		 * Notify attachable before execution
		 *
		 * Notifies attachable before the execution of the node
		 */
        virtual void notify_before() = 0;

		/**
		 * Notify attachable after execution
		 *
		 * Notifies attachable after the execution of the node
		 */
        virtual void notify_after() = 0;

        /**
         * Notify attachable after exiting
         *
         * Notifies attachable after the execution of the node
         */
        virtual void notify_exit() = 0;
	};

}

#endif