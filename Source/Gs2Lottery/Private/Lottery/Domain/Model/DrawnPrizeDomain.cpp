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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Lottery/Domain/Model/DrawnPrize.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FDrawnPrizeDomain::FDrawnPrizeDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DrawnPrize"
        ))
    {
    }

    FDrawnPrizeDomain::FDrawnPrizeDomain(
        const FDrawnPrizeDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FString FDrawnPrizeDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FDrawnPrizeDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FDrawnPrizeDomain::FModelTask::FModelTask(
        const TSharedPtr<FDrawnPrizeDomain> Self
    ): Self(Self)
    {

    }

    FDrawnPrizeDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDrawnPrizeDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lottery::Model::FDrawnPrize> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Lottery::Model::FDrawnPrize>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FDrawnPrizeDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDrawnPrizeDomain::FModelTask>> FDrawnPrizeDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDrawnPrizeDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDrawnPrizeDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FDrawnPrizePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FDrawnPrize::TypeName,
            ParentKey,
            Gs2::Lottery::Domain::Model::FDrawnPrizeDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FDrawnPrize>(obj));
            }
        );
    }

    void FDrawnPrizeDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FDrawnPrize::TypeName,
            ParentKey,
            Gs2::Lottery::Domain::Model::FDrawnPrizeDomain::CreateCacheKey(
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

