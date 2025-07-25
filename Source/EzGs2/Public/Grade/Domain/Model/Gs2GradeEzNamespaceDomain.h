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
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Model/Gs2GradeEzGradeModel.h"
#include "Grade/Model/Gs2GradeEzStatus.h"
#include "Grade/Model/Gs2GradeEzGradeEntryModel.h"
#include "Grade/Model/Gs2GradeEzAcquireAction.h"
#include "Grade/Model/Gs2GradeEzAcquireActionRate.h"
#include "Grade/Model/Gs2GradeEzVerifyActionResult.h"
#include "Grade/Model/Gs2GradeEzConsumeActionResult.h"
#include "Grade/Model/Gs2GradeEzAcquireActionResult.h"
#include "Grade/Model/Gs2GradeEzTransactionResult.h"
#include "Gs2GradeEzGradeModelDomain.h"
#include "Grade/Domain/Iterator/Gs2GradeEzDescribeGradeModelsIterator.h"
#include "Gs2GradeEzUserDomain.h"
#include "Gs2GradeEzUserDomain.h"
#include "Gs2GradeEzUserGameSessionDomain.h"
#include "Gs2GradeEzNamespaceDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Grade::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Grade::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Grade::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Grade::Domain::Iterator::FEzDescribeGradeModelsIteratorPtr GradeModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGradeModels(TFunction<void()> Callback);

        void UnsubscribeGradeModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Grade::Domain::Model::FEzGradeModelDomainPtr GradeModel(
            const FString GradeName
        ) const;

        Gs2::UE5::Grade::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Grade::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
