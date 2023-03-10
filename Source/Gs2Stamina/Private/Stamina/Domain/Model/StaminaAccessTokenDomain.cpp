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

#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/Stamina.h"
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

    FStaminaAccessTokenDomain::FStaminaAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> StaminaName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        StaminaName(StaminaName),
        ParentKey(Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Stamina"
        ))
    {
    }

    FStaminaAccessTokenDomain::FStaminaAccessTokenDomain(
        const FStaminaAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FStaminaAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self,
        const Request::FGetStaminaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->GetStamina(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStamina>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStaminaModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FGetTask>> FStaminaAccessTokenDomain::Get(
        Request::FGetStaminaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self,
        const Request::FConsumeStaminaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->ConsumeStamina(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStamina>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStaminaModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FConsumeTask>> FStaminaAccessTokenDomain::Consume(
        Request::FConsumeStaminaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::FSetMaxValueByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self,
        const Request::FSetMaxValueByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::FSetMaxValueByStatusTask(
        const FSetMaxValueByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->SetMaxValueByStatus(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStamina>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStaminaModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetMaxValueByStatusTask>> FStaminaAccessTokenDomain::SetMaxValueByStatus(
        Request::FSetMaxValueByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaxValueByStatusTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::FSetRecoverIntervalByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self,
        const Request::FSetRecoverIntervalByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::FSetRecoverIntervalByStatusTask(
        const FSetRecoverIntervalByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->SetRecoverIntervalByStatus(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStamina>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStaminaModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask>> FStaminaAccessTokenDomain::SetRecoverIntervalByStatus(
        Request::FSetRecoverIntervalByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverIntervalByStatusTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::FSetRecoverValueByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self,
        const Request::FSetRecoverValueByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::FSetRecoverValueByStatusTask(
        const FSetRecoverValueByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto Future = Self->Client->SetRecoverValueByStatus(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStamina>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Self->Cache->Put<Gs2::Stamina::Model::FStaminaModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask>> FStaminaAccessTokenDomain::SetRecoverValueByStatus(
        Request::FSetRecoverValueByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverValueByStatusTask>>(this->AsShared(), Request);
    }

    FString FStaminaAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> StaminaName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (StaminaName.IsSet() ? *StaminaName : "null") + ":" +
            ChildType;
    }

    FString FStaminaAccessTokenDomain::CreateCacheKey(
        TOptional<FString> StaminaName
    )
    {
        return FString() +
            (StaminaName.IsSet() ? *StaminaName : "null");
    }

    FStaminaAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStaminaAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Stamina::Model::FStamina>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                Self->StaminaName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetStaminaRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "stamina")
                    {
                        Self->Cache->Delete<Gs2::Stamina::Model::FStamina>(
                            Self->ParentKey,
                            Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Stamina::Model::FStamina>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    Self->StaminaName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>> FStaminaAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

