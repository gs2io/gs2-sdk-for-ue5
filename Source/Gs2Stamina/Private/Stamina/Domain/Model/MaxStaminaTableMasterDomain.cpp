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

#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FMaxStaminaTableMasterDomain::FMaxStaminaTableMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MaxStaminaTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        NamespaceName(NamespaceName),
        MaxStaminaTableName(MaxStaminaTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MaxStaminaTableMaster"
        ))
    {
    }

    FMaxStaminaTableMasterDomain::FMaxStaminaTableMasterDomain(
        const FMaxStaminaTableMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMaxStaminaTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
        const Request::FGetMaxStaminaTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMaxStaminaTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMaxStaminaTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FMaxStaminaTableMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMaxStaminaTableName(Self->MaxStaminaTableName);
        const auto Future = Self->Client->GetMaxStaminaTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MaxStaminaTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMaxStaminaTableMasterDomain::FGetTask>> FMaxStaminaTableMasterDomain::Get(
        Request::FGetMaxStaminaTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMaxStaminaTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
        const Request::FUpdateMaxStaminaTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMaxStaminaTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMaxStaminaTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMaxStaminaTableName(Self->MaxStaminaTableName);
        const auto Future = Self->Client->UpdateMaxStaminaTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MaxStaminaTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMaxStaminaTableMasterDomain::FUpdateTask>> FMaxStaminaTableMasterDomain::Update(
        Request::FUpdateMaxStaminaTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMaxStaminaTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMaxStaminaTableMasterDomain> Self,
        const Request::FDeleteMaxStaminaTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMaxStaminaTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMaxStaminaTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMaxStaminaTableName(Self->MaxStaminaTableName);
        const auto Future = Self->Client->DeleteMaxStaminaTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MaxStaminaTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMaxStaminaTableMasterDomain::FDeleteTask>> FMaxStaminaTableMasterDomain::Delete(
        Request::FDeleteMaxStaminaTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMaxStaminaTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MaxStaminaTableName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MaxStaminaTableName.IsSet() ? *MaxStaminaTableName : "null") + ":" +
            ChildType;
    }

    FString FMaxStaminaTableMasterDomain::CreateCacheKey(
        TOptional<FString> MaxStaminaTableName
    )
    {
        return FString() +
            (MaxStaminaTableName.IsSet() ? *MaxStaminaTableName : "null");
    }

    FMaxStaminaTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMaxStaminaTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FMaxStaminaTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMaxStaminaTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FMaxStaminaTableMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Stamina::Model::FMaxStaminaTableMaster>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                Self->MaxStaminaTableName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetMaxStaminaTableMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "maxStaminaTableMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                                Self->MaxStaminaTableName
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
            Value = Self->Cache->Get<Gs2::Stamina::Model::FMaxStaminaTableMaster>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain::CreateCacheKey(
                    Self->MaxStaminaTableName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMaxStaminaTableMasterDomain::FModelTask>> FMaxStaminaTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMaxStaminaTableMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

