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
#include "Experience/Domain/Model/StatusAccessToken.h"
#include "Experience/Model/Gs2ExperienceEzExperienceModel.h"
#include "Experience/Model/Gs2ExperienceEzThreshold.h"
#include "Experience/Model/Gs2ExperienceEzStatus.h"
#include "Experience/Model/Gs2ExperienceEzAcquireAction.h"
#include "Experience/Model/Gs2ExperienceEzAcquireActionRate.h"
#include "Gs2ExperienceEzStatusGameSessionDomain.h"
#include "Experience/Domain/Iterator/Gs2ExperienceEzDescribeStatusesIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Experience::Domain::Model
{

    class EZGS2_API FEzStatusGameSessionDomain final :
        public TSharedFromThis<FEzStatusGameSessionDomain>
    {
        Gs2::Experience::Domain::Model::FStatusAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> ExperienceName() const;
        TOptional<FString> PropertyId() const;

        FEzStatusGameSessionDomain(
            Gs2::Experience::Domain::Model::FStatusAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetStatusTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Model::FEzStatus>,
            public TSharedFromThis<FGetStatusTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FGetStatusTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Experience::Model::FEzStatus>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
        );

        class FGetStatusWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomain>,
            public TSharedFromThis<FGetStatusWithSignatureTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;
            FString KeyId;

        public:
            explicit FGetStatusWithSignatureTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomain>> Result
            ) override;
        };
        friend FGetStatusWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetStatusWithSignatureTask>> GetStatusWithSignature(
            FString KeyId
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Model::FEzStatus>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzStatusGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzStatusGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Experience::Model::FEzStatusPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzStatusGameSessionDomain> FEzStatusGameSessionDomainPtr;
}
