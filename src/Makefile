CC = gcc
$(shell mkdir -p $(BUILD_DIR)/src)
SRCS = $(shell find ./ -name "*.c")
DEPS = $(addprefix $(BUILD_DIR)/src/, $(addsuffix .d,$(SRCS)))
OBJS = $(addprefix $(BUILD_DIR)/src/, $(addsuffix .o,$(SRCS)))

all: $(BUILD_DIR)/liboopinc.a

$(BUILD_DIR)/liboopinc.a: $(YFO) $(filter-out $(LFO) $(BUILD_DIR)/src/./main.c.o,$(OBJS))
	@echo + AR $(notdir $@) >&2
	@ar rcs $@ $(filter-out $(LFO) $(BUILD_DIR)/src/./main.o,$(OBJS)) 

$(BUILD_DIR)/src/%.c.o: %.c $(YFC)
	@echo + CC src/$(notdir $<) >&2
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean:

-include $(DEPS)

.PHONY: clean all

