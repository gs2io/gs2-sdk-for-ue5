/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#include "Core/Util/Gs2Future.h"
#include "Misc/ScopeLock.h"


namespace Gs2::Core::Util
{

	TArray<TSharedPtr<FAsyncTaskBase>> RunningTasks;

	namespace
	{
		FCriticalSection RunningTasksMutex;
	}

	void RegisterRunningTask(const TSharedPtr<FAsyncTaskBase>& Task)
	{
		TArray<TSharedPtr<FAsyncTaskBase>> Retired;
		{
			FScopeLock Lock(&RunningTasksMutex);
			for (auto Iterator = RunningTasks.CreateIterator(); Iterator; ++Iterator)
			{
				if ((*Iterator).IsUnique() && (*Iterator)->IsDone())
				{
					Retired.Add(MoveTemp(*Iterator));
					Iterator.RemoveCurrent();
				}
			}
			RunningTasks.Add(Task);
		}
	}

#if PLATFORM_WINDOWS
	template class TGs2Future<void>;
#else
	template class GS2CORE_API TGs2Future<void>;
#endif

}
