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
#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Model/Gs2BuffEzBuffEntryModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetModel.h"
#include "Buff/Model/Gs2BuffEzBuffTargetAction.h"
#include "Buff/Model/Gs2BuffEzBuffTargetGrn.h"
#include "Gs2BuffEzBuffEntryModelDomain.h"
#include "Buff/Domain/Iterator/Gs2BuffEzDescribeBuffEntryModelsIterator.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Buff::Domain::Model
{

    class EZGS2_API FEzBuffEntryModelDomain final :
        public TSharedFromThis<FEzBuffEntryModelDomain>
    {
        Gs2::Buff::Domain::Model::FBuffEntryModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> BuffEntryName() const;

        FEzBuffEntryModelDomain(
            Gs2::Buff::Domain::Model::FBuffEntryModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Buff::Model::FEzBuffEntryModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzBuffEntryModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzBuffEntryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffEntryModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Buff::Model::FEzBuffEntryModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzBuffEntryModelDomain> FEzBuffEntryModelDomainPtr;
}
