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

#include "Lottery/Domain/Model/LotteryModel.h"
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

    FLotteryModelDomain::FLotteryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LotteryModel"
        ))
    {
    }

    FLotteryModelDomain::FLotteryModelDomain(
        const FLotteryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        LotteryName(From.LotteryName),
        ParentKey(From.ParentKey)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLotteryModelDomain>& Self,
        const Request::FGetLotteryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName);
        const auto Future = Self->Client->GetLotteryModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FGetTask>> FLotteryModelDomain::Get(
        Request::FGetLotteryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLotteryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LotteryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LotteryName.IsSet() ? *LotteryName : "null") + ":" +
            ChildType;
    }

    FString FLotteryModelDomain::CreateCacheKey(
        TOptional<FString> LotteryName
    )
    {
        return FString("") +
            (LotteryName.IsSet() ? *LotteryName : "null");
    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLotteryModelDomain> Self
    ): Self(Self)
    {

    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lottery::Model::FLotteryModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Lottery::Model::FLotteryModel>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                Self->LotteryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetLotteryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                    Self->LotteryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Lottery::Model::FLotteryModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "lotteryModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Lottery::Model::FLotteryModel>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                    Self->LotteryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FModelTask>> FLotteryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLotteryModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FLotteryModelDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FLotteryModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FLotteryModel::TypeName,
            ParentKey,
            Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                LotteryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FLotteryModel>(obj));
            }
        );
    }

    void FLotteryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FLotteryModel::TypeName,
            ParentKey,
            Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                LotteryName
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

