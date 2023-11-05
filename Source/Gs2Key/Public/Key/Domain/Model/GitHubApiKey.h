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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Key/Gs2Key.h"
#include "Key/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Key/Domain/Iterator/DescribeKeysIterator.h"
#include "Key/Domain/Iterator/DescribeGitHubApiKeysIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Key::Domain::Model
{
    class FNamespaceDomain;
    class FKeyDomain;
    class FGitHubApiKeyDomain;

    class GS2KEY_API FGitHubApiKeyDomain:
        public TSharedFromThis<FGitHubApiKeyDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Key::FGs2KeyRestClientPtr Client;

        public:
        TOptional<FString> ApiKey;
        TOptional<FString> GetApiKey() const
        {
            return ApiKey;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> ApiKeyName;
    private:

        FString ParentKey;

    public:

        FGitHubApiKeyDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ApiKeyName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGitHubApiKeyDomain(
            const FGitHubApiKeyDomain& From
        );

        class GS2KEY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FGitHubApiKeyDomain> Self;
            const Request::FUpdateGitHubApiKeyRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FGitHubApiKeyDomain> Self,
                const Request::FUpdateGitHubApiKeyRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateGitHubApiKeyRequestPtr Request
        );

        class GS2KEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FGitHubApiKey>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FGitHubApiKeyDomain> Self;
            const Request::FGetGitHubApiKeyRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FGitHubApiKeyDomain> Self,
                const Request::FGetGitHubApiKeyRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FGitHubApiKey>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetGitHubApiKeyRequestPtr Request
        );

        class GS2KEY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FGitHubApiKeyDomain> Self;
            const Request::FDeleteGitHubApiKeyRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FGitHubApiKeyDomain> Self,
                const Request::FDeleteGitHubApiKeyRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteGitHubApiKeyRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> ApiKeyName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ApiKeyName
        );

        class GS2KEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FGitHubApiKey>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FGitHubApiKeyDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FGitHubApiKeyDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FGitHubApiKey>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Key::Model::FGitHubApiKeyPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FGitHubApiKeyDomain> FGitHubApiKeyDomainPtr;
}
