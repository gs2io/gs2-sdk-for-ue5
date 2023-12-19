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

#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Formation::Domain::Iterator::FDescribeMoldsIteratorPtr FUserAccessTokenDomain::Molds(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeMolds(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Mold"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeMolds(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Mold"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FMoldAccessTokenDomain> FUserAccessTokenDomain::Mold(
        const FString MoldModelName
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FMoldAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            MoldModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MoldModelName)
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIteratorPtr FUserAccessTokenDomain::PropertyForms(
        const FString PropertyFormModelName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken,
            PropertyFormModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribePropertyForms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FPropertyForm::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "PropertyForm"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribePropertyForms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FPropertyForm::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "PropertyForm"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain> FUserAccessTokenDomain::PropertyForm(
        const FString PropertyFormModelName,
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FPropertyFormAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            PropertyFormModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyFormModelName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

