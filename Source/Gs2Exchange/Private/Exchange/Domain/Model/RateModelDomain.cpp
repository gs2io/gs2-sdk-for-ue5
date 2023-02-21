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

#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FRateModelDomain::FRateModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RateName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RateModel"
        ))
    {
    }

    FRateModelDomain::FRateModelDomain(
        const FRateModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FRateModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FRateModelDomain> Self,
        const Request::FGetRateModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRateModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FRateModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetRateModel(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Exchange::Model::FRateModel>(
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

    TSharedPtr<FAsyncTask<FRateModelDomain::FGetTask>> FRateModelDomain::Get(
        Request::FGetRateModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FRateModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RateName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RateName.IsSet() ? *RateName : "null") + ":" +
            ChildType;
    }

    FString FRateModelDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString() +
            (RateName.IsSet() ? *RateName : "null");
    }

    FRateModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FRateModelDomain> Self
    ): Self(Self)
    {

    }

    FRateModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FRateModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Exchange::Model::FRateModel>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                Self->RateName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetRateModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "rateModel")
                    {
                        Self->Cache->Delete<Gs2::Exchange::Model::FRateModel>(
                            Self->ParentKey,
                            Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                                Self->RateName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Exchange::Model::FRateModel>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                    Self->RateName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRateModelDomain::FModelTask>> FRateModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRateModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

