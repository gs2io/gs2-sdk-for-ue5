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

    class GS2KEY_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Key::FGs2KeyRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2KEY_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2KEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2KEY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2KEY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2KEY_API FCreateKeyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FKeyDomain>,
            public TSharedFromThis<FCreateKeyTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateKeyRequestPtr Request;
        public:
            explicit FCreateKeyTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateKeyRequestPtr Request
            );

            FCreateKeyTask(
                const FCreateKeyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
            ) override;
        };
        friend FCreateKeyTask;

        TSharedPtr<FAsyncTask<FCreateKeyTask>> CreateKey(
            Request::FCreateKeyRequestPtr Request
        );

        class GS2KEY_API FCreateGitHubApiKeyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>,
            public TSharedFromThis<FCreateGitHubApiKeyTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateGitHubApiKeyRequestPtr Request;
        public:
            explicit FCreateGitHubApiKeyTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FCreateGitHubApiKeyRequestPtr Request
            );

            FCreateGitHubApiKeyTask(
                const FCreateGitHubApiKeyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>> Result
            ) override;
        };
        friend FCreateGitHubApiKeyTask;

        TSharedPtr<FAsyncTask<FCreateGitHubApiKeyTask>> CreateGitHubApiKey(
            Request::FCreateGitHubApiKeyRequestPtr Request
        );

        Gs2::Key::Domain::Iterator::FDescribeKeysIteratorPtr Keys(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeKeys(
            TFunction<void()> Callback
        );

        void UnsubscribeKeys(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain> Key(
            const FString KeyName
        ) const;

        Gs2::Key::Domain::Iterator::FDescribeGitHubApiKeysIteratorPtr GitHubApiKeys(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGitHubApiKeys(
            TFunction<void()> Callback
        );

        void UnsubscribeGitHubApiKeys(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain> GitHubApiKey(
            const FString ApiKeyName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2KEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Key::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
