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


#include "Core/Domain/Model/JobQueueDomain.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Core::Domain::Model
{
    FJobQueueDomain::FJobQueueDomain(
        TFunction<bool (FString, Gs2::Auth::Model::FAccessTokenPtr)> RunFunc
    ): RunFunc(RunFunc)
    {
        
    }

    FJobQueueDomain::FJobQueueDomain(
        const FJobQueueDomain& From
    ): RunFunc(From.RunFunc)
    {
    }

    FJobQueueDomain::FRunTask::FRunTask(
        const TSharedPtr<FJobQueueDomain> Self,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
        
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobQueueDomain::FRunTask::Action(
        TSharedPtr<TSharedPtr<bool>> Result
    )
    {
        if (Self->Mutex.TryLock())
        {
            FString NamespaceName;
            if (Self->Tasks.Num() > 0)
            {
                NamespaceName = Self->Tasks[0];
            }
            if (NamespaceName.IsEmpty())
            {
                Self->Tasks.Remove(NamespaceName);
            } else
            {
                if (Self->RunFunc(NamespaceName, AccessToken))
                {
                    Self->Tasks.Remove(NamespaceName);
                }
            }
            *Result = MakeShared<bool>(Self->Tasks.Num() == 0);
            return nullptr;
        }
        *Result = MakeShared<bool>(true);
        return nullptr;
    }

    void FJobQueueDomain::Push(FString NamespaceName)
    {
        Tasks.Add(NamespaceName);
    }

    TSharedPtr<FAsyncTask<FJobQueueDomain::FRunTask>> FJobQueueDomain::Run(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(SharedThis(this), AccessToken);
    }

    FJobQueueExecutedEvent& FJobQueueDomain::OnExecutedEvent()
    {
        return JobQueueExecutedEvent;
    }
}
