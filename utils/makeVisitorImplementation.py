import re
import sys

def help_msg():
	print
	print("Please specify an interface to generate:")
	print("--SemanticAnalyser, -SA")
	print("--Executor, -E")
	print("--Printer, -P")
	print("--Hierarchy, -H")
	print("--Profiler, -PR")
	print("--Debugger, -D")
	print
	print("--All, -A")
	print
	exit()

if len(sys.argv) != 2:
	help_msg()

todo = []

if sys.argv[1] == "--SemanticAnalyser" or sys.argv[1] == "-SA" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "SemanticAnalyser",
		"visit_concrete_header" : "tr_semantic_analyser.h",
		"visit_concrete_src" : "tr_semantic_analyser.cpp",
		"class_scope" : "TRSemanticAnalyser::"
		})
if sys.argv[1] == "--Executor" or sys.argv[1] == "-E" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "Executor",
		"visit_concrete_header" : "tr_executor.h",
		"visit_concrete_src" : "tr_executor.cpp",
		"class_scope" : "TRExecutor::"
		})
if sys.argv[1] == "--Printer" or sys.argv[1] == "-P" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "Printer",
		"visit_concrete_header" : "tools/print_tree.h",
		"visit_concrete_src" : "tools/print_tree.cpp",
		"class_scope" : "PrintTree::"
		})
if sys.argv[1] == "--Hierarchy" or sys.argv[1] == "-H" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "Hierarchy",
		"visit_concrete_header" : "tools/tr_hierarchy.h",
		"visit_concrete_src" : "tools/tr_hierarchy.cpp",
		"class_scope" : "TRHierarchy::"
		})
if sys.argv[1] == "--Profiler" or sys.argv[1] == "-PR" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "Profiler",
		"visit_concrete_header" : "tools/tr_profiler.h",
		"visit_concrete_src" : "tools/tr_profiler.cpp",
		"class_scope" : "TRProfiler::"
		})
if sys.argv[1] == "--Debugger" or sys.argv[1] == "-D" or sys.argv[1] == "--All" or sys.argv[1] == "-A":
	todo.append({
		"name" : "Debugger",
		"visit_concrete_header" : "tools/tr_debugger.h",
		"visit_concrete_src" : "tools/tr_debugger.cpp",
		"class_scope" : "TRDebugger::"
		})

# if todo is empty then display help
if not todo:
	help_msg()

# check todo list for stuff to do
for component in todo:
	print("Doing: " + component["name"])
	visit_concrete_header = component["visit_concrete_header"]
	visit_concrete_src = component["visit_concrete_src"]
	class_scope = component["class_scope"]

	# file paths
	root_rel = "../"
	visit_interface = "AST/abstract_visitor.h"

	# regex captures
	start_inclusion_marker = "START INCLUSION POINT"
	end_inclusion_marker = "END INCLUSION POINT"
	interface_capture = "\s*(.+) = 0;$"
	indent_capture = "(\s*)//"
	name_capture = "(visit\w+)\("
	signature_sub = "virtual (.+) (visit.+\))"

	# file path combinations
	relative_visit_interface = root_rel + visit_interface
	relative_visit_concrete_header = root_rel + visit_concrete_header
	relative_visit_concrete_src = root_rel + visit_concrete_src

	# get all visitor functions from interface
	visit_fn = []
	with open(relative_visit_interface, 'r') as fin:
		for line in fin:
			m = re.search(interface_capture,line)
			if m:
				visit_fn.append(m.group(1))

	##############
	### HEADER ###
	##############

	# buffer header
	buffer = ""
	with open(relative_visit_concrete_header, 'r') as fin:
		buffer = fin.readlines()

	# find mark and remove previous content
	# find indentation size
	insert_idx = -1
	found = 0
	indentation = ""
	for i in range(0,len(buffer)):
		if re.search(start_inclusion_marker, buffer[i]):
			indentation = re.search(indent_capture, buffer[i]).group(1)
			insert_idx = i + 1
			found = 1
		if re.search(end_inclusion_marker, buffer[i]) and found == 1:
			del buffer[insert_idx:i]
			found = 2
			break

	if found == 0:
		print("Could not find start inclusion point:\n\t" + start_inclusion_marker)
		exit()
	if found == 1:
		print("Could not find end inclusion point:\n\t" + end_inclusion_marker)
		exit()

	# import all interface function
	for fn in visit_fn:
		inc = indentation + fn + ";\n"
		buffer.insert(insert_idx, inc)
		insert_idx += 1

	# write new file
	with open(relative_visit_concrete_header, 'w') as fout:
		fout.write("".join(buffer))


	##############
	### SOURCE ###
	##############

	# buffer header
	buffer = ""
	with open(relative_visit_concrete_src, 'r') as fin:
		buffer = fin.readlines()

	# array of name captures to insert
	name_array = [re.search(name_capture, n).group(1) for n in visit_fn]

	# find insertion spot
	# remove already prese visitor functions
	insert_idx = 0
	fn_idx = 0
	found = 0
	indentation = ""
	to_insert = []
	for i in range(0,len(buffer)):
		if re.search(start_inclusion_marker, buffer[i]):
			indentation = re.search(indent_capture, buffer[i]).group(1)
			found = 1

		# found an existing thing, so insert everything missing between this
		# and the next
		if re.search(name_capture, buffer[i]) and found == 1:
			current = re.search(name_capture, buffer[i]).group(1)

			# check if this is an interface function
			if current not in name_array:
				print("\"" + current + "\" is not in the interface: " + buffer[i].rstrip())
				to_insert.append([insert_idx, -1])

			else:
				if name_array[fn_idx] == current: # if in right order, progress index
					fn_idx += 1
				else: # otherwise insert and progress until we sync with current function
					while name_array[fn_idx] != current:
						to_insert.append([insert_idx, fn_idx])
						fn_idx += 1
						insert_idx += 1
					fn_idx += 1 # progress past sync function

		if re.search(end_inclusion_marker, buffer[i]) and found == 1:
			found = 2
			break

		insert_idx += 1 # progress insert by 1 line

	if found == 0:
		print("Could not find start inclusion point:\n\t" + start_inclusion_marker)
		exit()
	if found == 1:
		print("Could not find end inclusion point:\n\t" + end_inclusion_marker)
		exit()

	# add anything missed
	while fn_idx < len(visit_fn):
		to_insert.append([insert_idx, fn_idx])
		fn_idx += 1
		insert_idx += 1

	# insert all missing functions
	for insert_idx, fn_idx in to_insert:
		if fn_idx == -1: # notify about function not being in interface
			buffer.insert(insert_idx, indentation + "// FUNCTION NOT IN INTERFACE\n")
		else:
			m = re.search(signature_sub,visit_fn[fn_idx])
			fn = (indentation + m.group(1) + " " + class_scope + m.group(2) + " {\n" 
					+ indentation + "\treturn nullptr;\n"
					+ indentation + "}\n\n")
			buffer.insert(insert_idx, fn)

	# write new file
	with open(relative_visit_concrete_src, 'w') as fout:
		fout.write("".join(buffer))
