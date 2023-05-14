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

#include "Stamina/Domain/Model/StaminaModelMaster.h"
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

    FStaminaModelMasterDomain::FStaminaModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> StaminaName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        NamespaceName(NamespaceName),
        StaminaName(StaminaName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "StaminaModelMaster"
        ))
    {
    }

    FStaminaModelMasterDomain::FStaminaModelMasterDomain(
        const FStaminaModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FStaminaModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStaminaModelMasterDomain> Self,
        const Request::FGetStaminaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStaminaModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->GetStaminaModelMaster(
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
                    "StaminaModelMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStaminaModelMasterDomain::FGetTask>> FStaminaModelMasterDomain::Get(
        Request::FGetStaminaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStaminaModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStaminaModelMasterDomain> Self,
        const Request::FUpdateStaminaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->UpdateStaminaModelMaster(
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
                    "StaminaModelMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FStaminaModelMasterDomain::FUpdateTask>> FStaminaModelMasterDomain::Update(
        Request::FUpdateStaminaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStaminaModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStaminaModelMasterDomain> Self,
        const Request::FDeleteStaminaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->DeleteStaminaModelMaster(
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
                    "StaminaModelMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Stamina::Model::FStaminaModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaModelMasterDomain::FDeleteTask>> FStaminaModelMasterDomain::Delete(
        Request::FDeleteStaminaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStaminaModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> StaminaName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (StaminaName.IsSet() ? *StaminaName : "null") + ":" +
            ChildType;
    }

    FString FStaminaModelMasterDomain::CreateCacheKey(
        TOptional<FString> StaminaName
    )
    {
        return FString() +
            (StaminaName.IsSet() ? *StaminaName : "null");
    }

    FStaminaModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStaminaModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FStaminaModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStaminaModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Stamina::Model::FStaminaModelMaster>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                Self->StaminaName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetStaminaModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "staminaModelMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                                Self->StaminaName
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
            Value = Self->Cache->Get<Gs2::Stamina::Model::FStaminaModelMaster>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain::CreateCacheKey(
                    Self->StaminaName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaModelMasterDomain::FModelTask>> FStaminaModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStaminaModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

