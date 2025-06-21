CXX=nvcc
CXXFLAGS=-O3 -arch=compute_52
LDFLAGS=
CXXOBJDUMP=cuobjdump

TARGETS=scan-warp scan-block ballot-scan-warp-simple

all: $(TARGETS)

scan-warp: scan-warp.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
scan-block: scan-block.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
ballot-scan-warp-simple: ballot-scan-warp-simple.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.cu
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%.cubin: %.cu
	$(CXX) $(CXXFLAGS) --cubin -o $@ $<
%.isa: %.cubin
	$(CXXOBJDUMP) -sass $< > $@

.PHONY: clean all

clean:
	rm -f *.o *.ptx *.cubin *.isa *.log $(TARGETS)
