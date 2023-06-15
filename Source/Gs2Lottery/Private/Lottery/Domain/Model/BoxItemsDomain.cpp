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

#include "Lottery/Domain/Model/BoxItems.h"
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

    FBoxItemsDomain::FBoxItemsDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> PrizeTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        PrizeTableName(PrizeTableName),
        ParentKey(Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "BoxItems"
        ))
    {
    }

    FBoxItemsDomain::FBoxItemsDomain(
        const FBoxItemsDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FBoxItemsDomain::FGetTask::FGetTask(
        const TSharedPtr<FBoxItemsDomain> Self,
        const Request::FGetBoxByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBoxItemsDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->GetBoxByUserId(
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
                const auto ParentKey = Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "BoxItems"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FBoxItemsDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetPrizeTableName()
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FBoxItems::TypeName,
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

    TSharedPtr<FAsyncTask<FBoxItemsDomain::FGetTask>> FBoxItemsDomain::Get(
        Request::FGetBoxByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FBoxItemsDomain::FResetBoxTask::FResetBoxTask(
        const TSharedPtr<FBoxItemsDomain> Self,
        const Request::FResetBoxByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBoxItemsDomain::FResetBoxTask::FResetBoxTask(
        const FResetBoxTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsDomain::FResetBoxTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FBoxItemsDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->ResetBoxByUserId(
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
            
            {
                const auto ParentKey = Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "BoxItems"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FBoxItemsDomain::CreateCacheKey(
                    RequestModel->GetPrizeTableName()
                );
                Self->Cache->Delete(
                    Gs2::Lottery::Model::FBoxItems::TypeName,
                    ParentKey,
                    Key
                );
                Self->Cache->ClearListCache(
                    Gs2::Lottery::Model::FBoxItems::TypeName,
                    ParentKey
                );
            }
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBoxItemsDomain::FResetBoxTask>> FBoxItemsDomain::ResetBox(
        Request::FResetBoxByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FResetBoxTask>>(this->AsShared(), Request);
    }

    FString FBoxItemsDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> PrizeTableName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            ChildType;
    }

    FString FBoxItemsDomain::CreateCacheKey(
        TOptional<FString> PrizeTableName
    )
    {
        return FString() +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null");
    }

    FBoxItemsDomain::FModelTask::FModelTask(
        const TSharedPtr<FBoxItemsDomain> Self
    ): Self(Self)
    {

    }

    FBoxItemsDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBoxItemsDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FBoxItems>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lottery::Model::FBoxItems> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Lottery::Model::FBoxItems>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FBoxItemsDomain::CreateCacheKey(
                Self->PrizeTableName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetBoxByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Lottery::Domain::Model::FBoxItemsDomain::CreateCacheKey(
                    Self->PrizeTableName
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FBoxItems::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "boxItems")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Lottery::Model::FBoxItems>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FBoxItemsDomain::CreateCacheKey(
                    Self->PrizeTableName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBoxItemsDomain::FModelTask>> FBoxItemsDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBoxItemsDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

