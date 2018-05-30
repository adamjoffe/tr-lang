import glob
import re

root_rel = "../"
root_to_dir = "AST/"

# BUILD INCLUDE ALL FILE #
inc_all = "ast_concrete_nodes.h"
start_inclusion_marker = "START INCLUSION POINT"
end_inclusion_marker = "END INCLUSION POINT"
exclude_header = [
    "ast.*", # ignore all abstract types and tree components
    "abstract_visitor.h", # doesn't need visitor pattern interface
    "bi_func_decl.h" # exclude built in functions, since they aren't part of the interface and are templated
]

relative_dir = root_rel + root_to_dir

################
# INCLUDE LIST #
################

# populate buffer
buffer = ""
with open(relative_dir + inc_all, 'r') as fin:
    buffer = fin.readlines()


# remove previous inclusions and set include index
insert_idx = -1
found = 0
for i in range(0,len(buffer)):
    if re.search(start_inclusion_marker, buffer[i]):
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

# import all files in relative directory
for file in sorted(glob.glob(relative_dir + '*')):
    # ensure to only include .h files
    # exclude any excluded files
    if file != (relative_dir + inc_all) and re.search(".+\.h$", file) and all([not re.search(rgex, file) for rgex in exclude_header]):
        inc = "#include \"" + file.split('/')[-1] + "\"\n"
        buffer.insert(insert_idx, inc)
        insert_idx += 1

# write new file
with open(relative_dir + inc_all, 'w') as fout:
    fout.write("".join(buffer))


#####################
# VISITOR INTERFACE #
#####################

interace_all = "abstract_visitor.h"
start_impl_marker = "START INTERFACE POINT"
end_impl_marker = "END INTERFACE POINT"

buffer = ""
with open(relative_dir + interace_all, 'r') as fin:
    buffer = fin.readlines()

# remove previous inclusions and set include index
insert_idx = -1
indent = ""
found = 0
for i in range(0,len(buffer)):
    if re.search(start_impl_marker, buffer[i]):
        indent = re.search("(\s*)//",buffer[i]).group(1)
        insert_idx = i + 1
        found = 1
    if re.search(end_impl_marker, buffer[i]) and found == 1:
        del buffer[insert_idx:i]
        found = 2
        break

if found == 0:
    print("Could not find start inclusion point:\n\t" + start_impl_marker)
    exit()
if found == 1:
    print("Could not find end inclusion point:\n\t" + end_impl_marker)
    exit()

for file in sorted(glob.glob(relative_dir + '*')):
    if re.search(".+\.h$", file) and all([not re.search(rgex, file) for rgex in exclude_header]):
        with open(file,'r') as fdecl:
            for line in fdecl:
                m = re.search("class (\w+) :",line)
                if m:
                    definition = indent + "virtual ASTNode* visit" + m.group(1) + "(" + m.group(1) + "* ast, ASTNode* n) = 0;\n"
                    buffer.insert(insert_idx, definition)
                    insert_idx += 1

# write new file
with open(relative_dir + interace_all, 'w') as fout:
    fout.write("".join(buffer))

################
# VISITOR IMPL #
################

impl_all = "abstract_visitor.cpp"
start_impl_marker = "START IMPLEMENTATION POINT"
end_impl_marker = "END IMPLEMENTATION POINT"

buffer = ""
with open(relative_dir + impl_all, 'r') as fin:
    buffer = fin.readlines()


# remove previous inclusions and set include index
insert_idx = -1
indent = ""
found = 0
for i in range(0,len(buffer)):
    if re.search(start_impl_marker, buffer[i]):
        indent = re.search("(\s*)//",buffer[i]).group(1)
        insert_idx = i + 1
        found = 1
    if re.search(end_impl_marker, buffer[i]) and found == 1:
        del buffer[insert_idx:i]
        found = 2
        break

if found == 0:
    print("Could not find start inclusion point:\n\t" + start_impl_marker)
    exit()
if found == 1:
    print("Could not find end inclusion point:\n\t" + end_impl_marker)
    exit()

# pre space
buffer.insert(insert_idx, "\n")
insert_idx += 1

for file in sorted(glob.glob(relative_dir + '*')):
    if re.search(".+\.h$", file) and all([not re.search(rgex, file) for rgex in exclude_header]):
        with open(file,'r') as fdecl:
            for line in fdecl:
                m = re.search("class (\w+) :",line)
                if m:
                    definition = (indent + "ASTNode* " + m.group(1) + "::visit(Visitor* v, ASTNode* n) {\n" +
                        indent + "\t return v->visit" + m.group(1) + "(this, n);\n" +
                        indent + "}\n\n")
                    buffer.insert(insert_idx, definition)
                    insert_idx += 1

# write new file
with open(relative_dir + impl_all, 'w') as fout:
    fout.write("".join(buffer))