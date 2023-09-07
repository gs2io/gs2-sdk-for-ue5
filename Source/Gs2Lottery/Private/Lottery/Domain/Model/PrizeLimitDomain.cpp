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

#include "Lottery/Domain/Model/PrizeLimit.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FPrizeLimitDomain::FPrizeLimitDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PrizeTableName,
        const TOptional<FString> PrizeId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        NamespaceName(NamespaceName),
        PrizeTableName(PrizeTableName),
        PrizeId(PrizeId),
        ParentKey(Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheParentKey(
            NamespaceName,
            PrizeTableName,
            "PrizeLimit"
        ))
    {
    }

    FPrizeLimitDomain::FPrizeLimitDomain(
        const FPrizeLimitDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PrizeTableName(From.PrizeTableName),
        PrizeId(From.PrizeId),
        ParentKey(From.ParentKey)
    {

    }

    FPrizeLimitDomain::FGetTask::FGetTask(
        const TSharedPtr<FPrizeLimitDomain> Self,
        const Request::FGetPrizeLimitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeLimitDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithPrizeId(Self->PrizeId);
        const auto Future = Self->Client->GetPrizeLimit(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->PrizeTableName,
                    "PrizeLimit"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FPrizeLimitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPrizeId()
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FPrizeLimit::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FGetTask>> FPrizeLimitDomain::Get(
        Request::FGetPrizeLimitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPrizeLimitDomain::FResetTask::FResetTask(
        const TSharedPtr<FPrizeLimitDomain> Self,
        const Request::FResetPrizeLimitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeLimitDomain::FResetTask::FResetTask(
        const FResetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName)
            ->WithPrizeId(Self->PrizeId);
        const auto Future = Self->Client->ResetPrizeLimit(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FResetTask>> FPrizeLimitDomain::Reset(
        Request::FResetPrizeLimitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(this->AsShared(), Request);
    }

    FString FPrizeLimitDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PrizeTableName,
        TOptional<FString> PrizeId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            (PrizeId.IsSet() ? *PrizeId : "null") + ":" +
            ChildType;
    }

    FString FPrizeLimitDomain::CreateCacheKey(
        TOptional<FString> PrizeId
    )
    {
        return FString("") +
            (PrizeId.IsSet() ? *PrizeId : "null");
    }

    FPrizeLimitDomain::FModelTask::FModelTask(
        const TSharedPtr<FPrizeLimitDomain> Self
    ): Self(Self)
    {

    }

    FPrizeLimitDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeLimitDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeLimit>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lottery::Model::FPrizeLimit> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Lottery::Model::FPrizeLimit>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FPrizeLimitDomain::CreateCacheKey(
                Self->PrizeId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetPrizeLimitRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Lottery::Domain::Model::FPrizeLimitDomain::CreateCacheKey(
                    Self->PrizeId
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FPrizeLimit::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "prizeLimit")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Lottery::Model::FPrizeLimit>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FPrizeLimitDomain::CreateCacheKey(
                    Self->PrizeId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeLimitDomain::FModelTask>> FPrizeLimitDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPrizeLimitDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

