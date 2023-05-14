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

#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FLimitModelMasterDomain::FLimitModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LimitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Session)),
        NamespaceName(NamespaceName),
        LimitName(LimitName),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LimitModelMaster"
        ))
    {
    }

    FLimitModelMasterDomain::FLimitModelMasterDomain(
        const FLimitModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FLimitModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FLimitModelMasterDomain> Self,
        const Request::FGetLimitModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLimitModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName);
        const auto Future = Self->Client->GetLimitModelMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "LimitModelMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FLimitModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FLimitModelMasterDomain::FGetTask>> FLimitModelMasterDomain::Get(
        Request::FGetLimitModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FLimitModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FLimitModelMasterDomain> Self,
        const Request::FUpdateLimitModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLimitModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName);
        const auto Future = Self->Client->UpdateLimitModelMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "LimitModelMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FLimitModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FLimitModelMasterDomain::FUpdateTask>> FLimitModelMasterDomain::Update(
        Request::FUpdateLimitModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FLimitModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FLimitModelMasterDomain> Self,
        const Request::FDeleteLimitModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLimitModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FLimitModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName);
        const auto Future = Self->Client->DeleteLimitModelMaster(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "LimitModelMaster"
                );
                const auto Key = Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Limit::Model::FLimitModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLimitModelMasterDomain::FDeleteTask>> FLimitModelMasterDomain::Delete(
        Request::FDeleteLimitModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FLimitModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LimitName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LimitName.IsSet() ? *LimitName : "null") + ":" +
            ChildType;
    }

    FString FLimitModelMasterDomain::CreateCacheKey(
        TOptional<FString> LimitName
    )
    {
        return FString() +
            (LimitName.IsSet() ? *LimitName : "null");
    }

    FLimitModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FLimitModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FLimitModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Limit::Model::FLimitModelMaster>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                Self->LimitName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetLimitModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "limitModelMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Limit::Model::FLimitModelMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                                Self->LimitName
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
            Value = Self->Cache->Get<Gs2::Limit::Model::FLimitModelMaster>(
                Self->ParentKey,
                Gs2::Limit::Domain::Model::FLimitModelMasterDomain::CreateCacheKey(
                    Self->LimitName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLimitModelMasterDomain::FModelTask>> FLimitModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLimitModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

