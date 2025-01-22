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
#include "Grade/Domain/Model/GradeModel.h"
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
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Grade::Domain::Model
{

    class EZGS2_API FEzGradeModelDomain final :
        public TSharedFromThis<FEzGradeModelDomain>
    {
        Gs2::Grade::Domain::Model::FGradeModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> GradeName() const;

        FEzGradeModelDomain(
            Gs2::Grade::Domain::Model::FGradeModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Grade::Model::FEzGradeModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzGradeModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzGradeModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Grade::Model::FEzGradeModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzGradeModelDomain> FEzGradeModelDomainPtr;
}
