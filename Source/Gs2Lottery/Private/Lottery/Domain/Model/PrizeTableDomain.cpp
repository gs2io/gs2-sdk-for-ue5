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

#include "Lottery/Domain/Model/PrizeTable.h"
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

    FPrizeTableDomain::FPrizeTableDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PrizeTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        NamespaceName(NamespaceName),
        PrizeTableName(PrizeTableName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PrizeTable"
        ))
    {
    }

    FPrizeTableDomain::FPrizeTableDomain(
        const FPrizeTableDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        PrizeTableName(From.PrizeTableName),
        ParentKey(From.ParentKey)
    {

    }

    FPrizeTableDomain::FGetTask::FGetTask(
        const TSharedPtr<FPrizeTableDomain> Self,
        const Request::FGetPrizeTableRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeTableDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->GetPrizeTable(
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
                const auto ParentKey = Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "PrizeTable"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FPrizeTable::TypeName,
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

    TSharedPtr<FAsyncTask<FPrizeTableDomain::FGetTask>> FPrizeTableDomain::Get(
        Request::FGetPrizeTableRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Lottery::Domain::Iterator::FDescribePrizeLimitsIteratorPtr FPrizeTableDomain::PrizeLimits(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribePrizeLimitsIterator>(
            Cache,
            Client,
            NamespaceName,
            PrizeTableName
        );
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeLimitDomain> FPrizeTableDomain::PrizeLimit(
        const FString PrizeId
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FPrizeLimitDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            PrizeTableName,
            PrizeId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PrizeId)
        );
    }

    FString FPrizeTableDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PrizeTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            ChildType;
    }

    FString FPrizeTableDomain::CreateCacheKey(
        TOptional<FString> PrizeTableName
    )
    {
        return FString("") +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null");
    }

    FPrizeTableDomain::FModelTask::FModelTask(
        const TSharedPtr<FPrizeTableDomain> Self
    ): Self(Self)
    {

    }

    FPrizeTableDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTable>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Lottery::Model::FPrizeTable> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Lottery::Model::FPrizeTable>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheKey(
                Self->PrizeTableName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetPrizeTableRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheKey(
                    Self->PrizeTableName
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FPrizeTable::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "prizeTable")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Lottery::Model::FPrizeTable>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FPrizeTableDomain::CreateCacheKey(
                    Self->PrizeTableName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeTableDomain::FModelTask>> FPrizeTableDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPrizeTableDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

