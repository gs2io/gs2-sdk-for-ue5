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

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "../../Model/Region.h"
#include "../../Net/Gs2Session.h"

namespace Gs2::Core::Net::Rest
{
    namespace Task
    {
        class GS2CORE_API FRestOpenTask;
        class GS2CORE_API FRestReOpenTask;
        class GS2CORE_API FRestCloseTask;
    }
    
    class GS2CORE_API FGs2RestSession final :
        public IGs2Session,
        public TSharedFromThis<FGs2RestSession>
    {
        Model::FGs2CredentialPtr CredentialValue;
        Model::ERegion RegionValue;
        FString OwnerIdValue;

    public:
        explicit FGs2RestSession(
            const Model::FGs2CredentialPtr Credential
        );
        FGs2RestSession(
            const FGs2RestSession& From
        );
    
        FGs2RestSession(
            const Model::FGs2CredentialPtr Credential,
            const Model::ERegion Region
        );

        TSharedPtr<FAsyncTask<Task::FRestOpenTask>> Open();
        TSharedPtr<FAsyncTask<Task::FRestReOpenTask>> ReOpen();
        TSharedPtr<FAsyncTask<Task::FRestCloseTask>> Close();
        
        virtual FString OwnerId() const override;
        virtual void SetOwnerId(FString OwnerId);
        virtual Model::ERegion Region() const override;
        virtual FString RegionName() const override;
        virtual Model::FGs2CredentialPtr Credential() const override;
    };
	typedef TSharedPtr<FGs2RestSession, ESPMode::ThreadSafe> FGs2RestSessionPtr;
}
