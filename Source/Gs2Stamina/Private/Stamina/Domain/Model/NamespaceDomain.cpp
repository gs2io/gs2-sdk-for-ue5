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

#include "Stamina/Domain/Model/Namespace.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("stamina:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateMaxStaminaTableMasterTask::FCreateMaxStaminaTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateMaxStaminaTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateMaxStaminaTableMasterTask::FCreateMaxStaminaTableMasterTask(
        const FCreateMaxStaminaTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateMaxStaminaTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateMaxStaminaTableMasterTask>> FNamespaceDomain::CreateMaxStaminaTableMaster(
        Request::FCreateMaxStaminaTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMaxStaminaTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::FCreateRecoverIntervalTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::FCreateRecoverIntervalTableMasterTask(
        const FCreateRecoverIntervalTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRecoverIntervalTableMasterTask>> FNamespaceDomain::CreateRecoverIntervalTableMaster(
        Request::FCreateRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRecoverIntervalTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRecoverValueTableMasterTask::FCreateRecoverValueTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRecoverValueTableMasterTask::FCreateRecoverValueTableMasterTask(
        const FCreateRecoverValueTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRecoverValueTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRecoverValueTableMasterTask>> FNamespaceDomain::CreateRecoverValueTableMaster(
        Request::FCreateRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRecoverValueTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStaminaModelMasterTask::FCreateStaminaModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStaminaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStaminaModelMasterTask::FCreateStaminaModelMasterTask(
        const FCreateStaminaModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStaminaModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStaminaModelMasterTask>> FNamespaceDomain::CreateStaminaModelMaster(
        Request::FCreateStaminaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStaminaModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain> FNamespaceDomain::CurrentStaminaMaster(
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeMaxStaminaTableMastersIteratorPtr FNamespaceDomain::MaxStaminaTableMasters(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeMaxStaminaTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeMaxStaminaTableMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "MaxStaminaTableMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeMaxStaminaTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "MaxStaminaTableMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain> FNamespaceDomain::MaxStaminaTableMaster(
        const FString MaxStaminaTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            MaxStaminaTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MaxStaminaTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIteratorPtr FNamespaceDomain::StaminaModels(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StaminaModel"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStaminaModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StaminaModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelDomain> FNamespaceDomain::StaminaModel(
        const FString StaminaName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            StaminaName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StaminaName)
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeRecoverIntervalTableMastersIteratorPtr FNamespaceDomain::RecoverIntervalTableMasters(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeRecoverIntervalTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverIntervalTableMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RecoverIntervalTableMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRecoverIntervalTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RecoverIntervalTableMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain> FNamespaceDomain::RecoverIntervalTableMaster(
        const FString RecoverIntervalTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RecoverIntervalTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RecoverIntervalTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeRecoverValueTableMastersIteratorPtr FNamespaceDomain::RecoverValueTableMasters(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeRecoverValueTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverValueTableMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RecoverValueTableMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeRecoverValueTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "RecoverValueTableMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain> FNamespaceDomain::RecoverValueTableMaster(
        const FString RecoverValueTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RecoverValueTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RecoverValueTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelMastersIteratorPtr FNamespaceDomain::StaminaModelMasters(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StaminaModelMaster"
            ),
            Callback
        );
    }

    void FNamespaceDomain::UnsubscribeStaminaModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                NamespaceName,
                "StaminaModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain> FNamespaceDomain::StaminaModelMaster(
        const FString StaminaName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            StaminaName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StaminaName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("stamina:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FNamespace> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FNamespace>(
            ParentKey,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FNamespace>(
                ParentKey,
                Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FNamespace>(obj));
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
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

