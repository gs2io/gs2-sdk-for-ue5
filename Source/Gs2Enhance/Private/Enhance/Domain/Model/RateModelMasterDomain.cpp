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

#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Enhance::Domain::Model
{

    FRateModelMasterDomain::FRateModelMasterDomain(
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
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Session)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RateModelMaster"
        ))
    {
    }

    FRateModelMasterDomain::FRateModelMasterDomain(
        const FRateModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FRateModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRateModelMasterDomain> Self,
        const Request::FGetRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRateModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FRateModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetRateModelMaster(
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
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RateModelMaster"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enhance::Model::FRateModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRateModelMasterDomain::FGetTask>> FRateModelMasterDomain::Get(
        Request::FGetRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRateModelMasterDomain> Self,
        const Request::FUpdateRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRateModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->UpdateRateModelMaster(
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
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RateModelMaster"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enhance::Model::FRateModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRateModelMasterDomain::FUpdateTask>> FRateModelMasterDomain::Update(
        Request::FUpdateRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRateModelMasterDomain> Self,
        const Request::FDeleteRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRateModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->DeleteRateModelMaster(
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
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RateModelMaster"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Enhance::Model::FRateModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRateModelMasterDomain::FDeleteTask>> FRateModelMasterDomain::Delete(
        Request::FDeleteRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRateModelMasterDomain::CreateCacheParentKey(
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

    FString FRateModelMasterDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString() +
            (RateName.IsSet() ? *RateName : "null");
    }

    FRateModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRateModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FRateModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRateModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FRateModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Enhance::Model::FRateModelMaster>(
            Self->ParentKey,
            Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
                Self->RateName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enhance::Request::FGetRateModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "rateModelMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Enhance::Model::FRateModelMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Enhance::Model::FRateModelMaster>(
                Self->ParentKey,
                Gs2::Enhance::Domain::Model::FRateModelMasterDomain::CreateCacheKey(
                    Self->RateName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRateModelMasterDomain::FModelTask>> FRateModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRateModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

