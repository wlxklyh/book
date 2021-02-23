import os
import sys

cmd_start_cacheserver = "cd /Users/Shared/CacheServerGWGO/ \n node --max-old-space-size=16384 /usr/local/bin/unity-cache-server -l 5 --NODE_CONFIG_DIR=/Users/Shared/CacheServerGWGO/config"
result = -1
while result != 0:
result = os.system(cmd_start_cacheserver)