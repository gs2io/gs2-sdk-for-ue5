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

#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FPropertyFormAccessTokenDomain::FPropertyFormAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> FormModelName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        FormModelName(FormModelName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "PropertyForm"
        ))
    {
    }

    FPropertyFormAccessTokenDomain::FPropertyFormAccessTokenDomain(
        const FPropertyFormAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FPropertyFormAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
        const Request::FGetPropertyFormRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyForm>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFormModelName(Self->FormModelName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetPropertyForm(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Formation::Model::FPropertyForm>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put<Gs2::Formation::Model::FFormModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormAccessTokenDomain::FGetTask>> FPropertyFormAccessTokenDomain::Get(
        Request::FGetPropertyFormRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPropertyFormAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
        const Request::FGetPropertyFormWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormAccessTokenDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFormModelName(Self->FormModelName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetPropertyFormWithSignature(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Formation::Model::FPropertyForm>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put<Gs2::Formation::Model::FFormModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormAccessTokenDomain::FGetWithSignatureTask>> FPropertyFormAccessTokenDomain::GetWithSignature(
        Request::FGetPropertyFormWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FPropertyFormAccessTokenDomain::FSetWithSignatureTask::FSetWithSignatureTask(
        const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
        const Request::FSetPropertyFormWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormAccessTokenDomain::FSetWithSignatureTask::FSetWithSignatureTask(
        const FSetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormAccessTokenDomain::FSetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFormModelName(Self->FormModelName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SetPropertyFormWithSignature(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Self->Cache->Put<Gs2::Formation::Model::FPropertyForm>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Put<Gs2::Formation::Model::FFormModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormAccessTokenDomain::FSetWithSignatureTask>> FPropertyFormAccessTokenDomain::SetWithSignature(
        Request::FSetPropertyFormWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetWithSignatureTask>>(this->AsShared(), Request);
    }

    FPropertyFormAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPropertyFormAccessTokenDomain> Self,
        const Request::FDeletePropertyFormRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPropertyFormAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithFormModelName(Self->FormModelName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->DeletePropertyForm(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Self->Cache->Delete<Gs2::Formation::Model::FPropertyForm>(ParentKey, Key);
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                    ResultModel->GetFormModel()->GetName()
                );
                Self->Cache->Delete<Gs2::Formation::Model::FFormModel>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormAccessTokenDomain::FDeleteTask>> FPropertyFormAccessTokenDomain::Delete(
        Request::FDeletePropertyFormRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPropertyFormAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> FormModelName,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (FormModelName.IsSet() ? *FormModelName : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FPropertyFormAccessTokenDomain::CreateCacheKey(
        TOptional<FString> FormModelName,
        TOptional<FString> PropertyId
    )
    {
        return FString() +
            (FormModelName.IsSet() ? *FormModelName : "null") + ":" + 
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FPropertyFormAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FPropertyFormAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FPropertyFormAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPropertyFormAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyForm>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Formation::Model::FPropertyForm>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                Self->FormModelName,
                Self->PropertyId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetPropertyFormRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "propertyForm")
                    {
                        Self->Cache->Delete<Gs2::Formation::Model::FPropertyForm>(
                            Self->ParentKey,
                            Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                                Self->FormModelName,
                                Self->PropertyId
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
            Value = Self->Cache->Get<Gs2::Formation::Model::FPropertyForm>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    Self->FormModelName,
                    Self->PropertyId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPropertyFormAccessTokenDomain::FModelTask>> FPropertyFormAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPropertyFormAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

